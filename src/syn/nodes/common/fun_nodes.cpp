#include "syn/nodes/common/fun_nodes.hpp"

#include <algorithm>
#include <optional>
#include <string>
#include <utility>

#include "esl/category.hpp"
#include "esl/lift.hpp"
#include "esl/ranges.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/zip.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "sem/compound.hpp"
#include "sem/declarations.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::syn::fun_nodes {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::StatementProcessingResult;
    using sem::CaptureVector;
    using sem::CompleteValue;
    using sem::FunctionDefinition;
    using sem::Integral;
    using sem::NoReturn;
    using sem::ResolvedCapture;
    using sem::TypedName;

    std::string runtimeCapture (
        context::Main            & ctx,
        std::vector<std::string> & declarations,
        std::vector<std::string> & assignments,
        std::string const        & closureName, // I'm aware of this unused param. I'll remove it when I test that everything is ok.
        std::string const        & type,
        std::string const        & variable
    ) {
        auto captureName = c::variableName(c::id(ctx.nextId()));
        auto decl        = c::declaration(type, captureName);
        //auto assgn       = c::statement(closureName + c::designatedInitialization(variable, captureName));
        auto assgn       = c::designatedInitialization(variable, captureName);
        declarations.push_back(decl);
        assignments.push_back(assgn);
        return captureName;
    }

    namespace {

        template <esl::range R>
        void makeRangeUnique (R & values) {
            std::sort(values.begin(), values.end());
            values.erase(std::unique(values.begin(), values.end()), values.end());
        }

    }

    esl::result<CaptureResult> capture (
        context::Main & ctx,
        std::vector<std::string> const & names_,
        std::vector<std::string> const & typeNames_
    ) { // TODO: Why can't I take names and typeNames by value?
        CaptureResult            result;
        std::vector<std::string> declarations; // <type> <name>
        std::vector<std::string> assignments;  // <closure>.<name> = <var>;

        // TODO: Take them by value instead...
        std::vector<std::string> names     = names_;
        std::vector<std::string> typeNames = typeNames_;
        makeRangeUnique(names);
        makeRangeUnique(typeNames);

        auto closureName = c::closureVariableName(c::id(ctx.nextId()));

        for (auto const & name: typeNames) {
            auto type = ctx.lookup.findType(name);
            if (!type)
                return esl::result_error{"Type name not found."};
            result.closure.types.emplace(std::make_pair(name, *type));
        }

        for (auto const & name: names) {
            CaptureVector<ResolvedCapture> capturedTuple;

            auto value = ctx.lookup.findValue(name);
            if (!value)
                return esl::result_error{"Name `" + name + "` not found."};

            for (auto const & var: *value) {
                auto captureResult = [&] (CompleteValue const & varVal) {
                    return [&] (sem::value::Function fun) -> esl::result<void> {
                        // Capturing a function (a partially run-time value):
                        if (!fun.closureVariable) {
                            // Fully comp-time closure:
                            capturedTuple.emplace_back(varVal);
                            return {};
                        }
                        if (!fun.definition.closureType) // Implementation error.
                            return esl::result_error{"No closure type in a captured function with a closure variable."};
                        // Run-time closure:
                        auto capturedMember = runtimeCapture(
                            ctx, declarations, assignments, closureName,
                            *fun.definition.closureType, *fun.closureVariable
                        );
                        auto copy = sem::value::Function{
                            fun.definition,
                            c::memberAccess(c::closureArgumentName(), capturedMember)
                        };
                        capturedTuple.emplace_back(CompleteValue{copy});
                        return {};

                    } | [&] (auto) -> esl::result<void> {
                        // Capturing a comp-time value:
                        capturedTuple.emplace_back(varVal);
                        return {};

                    } || target::category{} <<= varVal;

                } | [&] (TypedName const & varName) {
                    // Capturing a run-time variable:
                    return [&] (auto const & type) -> esl::result<void> {
                        auto capturedMember = runtimeCapture(
                            ctx, declarations, assignments,
                            closureName, type, varName.name
                        );
                        auto captureType = varName.type;
                        //using Type = decltype(captureType);
                        // TODO: This (simple || array) should be in interface/types and interface/values
                        // (as interface::mutableType and interface::mutableValue or something)
                        /* TODO: This would be nice, but there are some problems with assigning structs with const members to unions.
                        [] <typename Type> (Type & type) requires (
                            interface::simpleType<Type> || esl::same_but_cvref<Type, sem::type::Array>
                        ) {
                            type.constant = true;
                        } | [] (auto &) {
                            // Skip. These are always cosnt.
                        } || target::category{} <<= captureType;
                        */
                        capturedTuple.emplace_back(TypedName{
                            .type = captureType,
                            .name = c::memberAccess(c::closureArgumentName(), capturedMember)
                            // TODO: This should be in translation.hpp (as c::pointerMemberAccess or something)
                            //.name = c::closureArgumentName() + "->" + capturedMember
                        });
                        return {};

                    } || target::result{} <<=
                        interface::translateType || target::category{} <<= varName.type;

                } || target::category{} <<= var;
                if (!captureResult) return captureResult.error();
            }

            result.closure.values.emplace(std::make_pair(name, capturedTuple));
        }

        if (!declarations.empty() || !assignments.empty()) {
            // Closure type definition:
            result.closureVariable = closureName;
            // TODO: There should be 2 separate functions in translation.hpp (closureTypeName and closureType)
            auto closureTypeName   = c::closureType(c::id(ctx.nextId()));
            result.closureType     = c::structure(closureTypeName);
            auto closureStruct     = c::statement(c::structureDefinition(closureTypeName, declarations));
            //auto closureDef        = c::statement(c::declaration(*result.closureType, *result.closureVariable));
            auto closureDef        = c::statement(
                c::definition(*result.closureType, *result.closureVariable, c::init(assignments))
            );

            /***
            struct <closure> {
                <declaration1>;
                ...
            };
            ***/
            ctx.global.insertType(closureStruct);

            /***
            <closuretype> <closurevar>;
            ***/
            //ctx.insertStatement(closureDef);

            // Closure variable initialization:
            /*
            for (auto const & assgn: assignments) {
                ctx.insertStatement(assgn);
            }
            */

            /***
            <closuretype> <closurevar> {
                <assignment1>,
                <assignment2>,
                ...
            };
            ***/
            ctx.insertStatement(closureDef);
        }

        return result;
    }

    esl::result<sem::value::Function> process (
        context::Main               & ctx,
        category::Type        const & output,
        category::Declaration const & input,
        category::Expression  const & body
    ) {
        return [&] (auto outTypes, auto inDecls) -> esl::result<sem::value::Function> {
            //auto paramScope = ctx.makeScopeChild();
            context::Lookup paramScope;

            for (auto const & decl: inDecls) {
                auto lookupResult = paramScope.insertValue(decl.name, {});
                if (!lookupResult)
                    return esl::result_error{"Cannot redeclare a parameter"};
            }

            return [&] (auto names, auto typeNames) {
                return [&] (auto captured) -> esl::result<sem::value::Function> {
                    auto const & [closure, closureType, closureVariable] = captured;

                    auto inParams = interface::resolveParameter || target::tiny_vector{} <<= inDecls;
                    auto inTypes  = interface::declType         || target::nested_tiny_vector_cat{} <<= inDecls;

                    auto & def = ctx.global.storeValue(FunctionDefinition{
                        .implementation = FunctionDefinition::Implementation{
                            .parameters = inParams,
                            .body       = body,
                            .closure    = closure
                        },
                        .type = sem::type::Function{
                            .in  = esl::make_component_vector(inTypes),
                            .out = esl::make_component_vector(outTypes)
                        },
                        .closureType = closureType, // If capturing some run-time values.
                        .name        = std::nullopt // Will be generated at deifnition.
                    });

                    return sem::value::Function{def, closureVariable};

                } || target::result{} <<= fun_nodes::capture(ctx, (names), (typeNames));

            } || target::result{} <<= args(
                //interface::extractNames(paramScope.lookup)     || target::category{} <<= body,
                //interface::extractTypeNames(paramScope.lookup) || target::category{} <<= body
                interface::extractNames(paramScope)     || target::category{} <<= body,
                interface::extractTypeNames(paramScope) || target::category{} <<= body
            );

        } || target::result{} <<= args(
            interface::resolveType(ctx)        || target::category{} <<= output,
            interface::resolveDeclaration(ctx) || target::category{} <<= input
        );
    }

}
