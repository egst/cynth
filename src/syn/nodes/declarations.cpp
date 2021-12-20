#include "syn/nodes/declarations.hpp"

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/containers.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"

#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"

namespace esl {

    using cynth::syn::node::Declaration;
    using cynth::syn::node::TupleDecl;

    template <>
    void component_deleter<Declaration>::operator () (Declaration * ptr) const {
        delete ptr;
    }

    template <>
    Declaration * component_allocator<Declaration>::operator () (Declaration const & other) const {
        return new Declaration{other};
    }

    template <>
    Declaration * component_allocator<Declaration>::operator () (Declaration && other) const {
        return new Declaration{std::move(other)};
    }

    template <>
    void component_deleter<TupleDecl>::operator () (TupleDecl * ptr) const {
        delete ptr;
    }

    template <>
    TupleDecl * component_allocator<TupleDecl>::operator () (TupleDecl const & other) const {
        return new TupleDecl{other};
    }

    template <>
    TupleDecl * component_allocator<TupleDecl>::operator () (TupleDecl && other) const {
        return new TupleDecl{std::move(other)};
    }

}

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using esl::lift;
    using interface::DeclarationResolutionResult;
    using interface::DisplayResult;
    using interface::StatementProcessingResult;
    using sem::CompleteDeclaration;
    using sem::NoReturn;
    using sem::Variable;

    namespace {

        StatementProcessingResult processStatementImpl (context::C & ctx, interface::node auto const & decl) {
            return [&] (auto decls) -> StatementProcessingResult {
                for (auto const & decl : decls) {
                    auto result = [&] (auto vars) {
                        return ctx.comptime().insertValue(decl.name, vars);

                    } || target::result{} <<=
                    esl::unite_results <<=
                    [&ctx] (auto const & type) -> esl::result<Variable> {
                        return interface::processDeclaration(ctx)(type);

                    } || target::nested<target::component_vector_tiny_result, target::category>{} <<= decl.type;

                    if (!result) return result.error();
                }

                return {NoReturn{}};

            } || target::result{} <<= interface::resolveDeclaration(ctx)(decl);
        }

    }

    //// Declaration ////

    DisplayResult node::Declaration::display () const {
        return lift<target::component, target::category>(interface::display)(type) + " " + interface::display(name);
    }

    DeclarationResolutionResult node::Declaration::resolveDeclaration (context::C & ctx) const {
        return [&] (auto type) {
            return esl::init<esl::tiny_vector>(CompleteDeclaration{
                esl::make_component_vector(std::move(type)),
                *name.name
            });

        } || target::result {} <<= interface::resolveType(ctx) || target::category{} <<= *type;
    }

    StatementProcessingResult node::Declaration::processStatement (context::C & ctx) const {
        return processStatementImpl(ctx, *this);
    }

    //// TupleDecl ////

    DisplayResult node::TupleDecl::display () const {
        return
            "(" +
            esl::join(", ", lift<target::component_vector, target::category>(interface::display)(declarations)) +
            ")";
    }

    DeclarationResolutionResult node::TupleDecl::resolveDeclaration (context::C & ctx) const {
        DeclarationResolutionResult::value_type result;

        [&] (auto decls) {
            for (auto const & tuple: decls) for (auto const & value: tuple) {
                result.push_back(std::move(value));
            }

        } || target::result{} <<=
        esl::unite_results <<=
        interface::resolveDeclaration(ctx) || target::nested<target::component_vector, target::category>{} <<=
        declarations;

        return result;
    }

    StatementProcessingResult node::TupleDecl::processStatement (context::C & ctx) const {
        return processStatementImpl(ctx, *this);
    }

}
