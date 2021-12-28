#include "sem/types.hpp"

#include <functional>
#include <string>

#include "esl/boolean.hpp"
#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/component.hpp"
#include "esl/containers.hpp"
#include "esl/functional.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"

#include "context/main.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/numeric_types.hpp"

namespace cynth::sem {
#if 0 // TODO

    namespace {

        interface::DefinitionTranslationResult translateSimpleDefinition (
            context::C & ctx,
            std::optional<std::string> const & definition,
            std::string const & typeName
        ) {
            auto value   = definition.value_or("0");
            auto varName = c::variableName(std::to_string(ctx.nextId()));

            auto local = c::definition(c::typeName(typeName), varName, value);

            /***
            local:
            cth_<type> var_<i = nextId()> = <definition>;
            ***/
            auto result = ctx.insertStatement(local);
            if (!result)
                return result.error();

            /***
            var_<i>
            ***/
            return varName;
        }

        template <typename... Ts>
        interface::AllocationTranslationResult translateArrayAllocation (
            context::C & ctx,
            std::optional<std::string> init,
            std::string size,
            Ts const &... types
        ) {
            auto valName = c::valueName(std::to_string(ctx.nextId()));
            auto valType = c::arrayValueType(size, types...);
            auto alloc = init
                ? c::statement(c::definition(valType, valName, *init))
                : c::statement(c::declaration(valType, valName));

            /***
            function:
            struct cth_arr$<size>$<type1>$<type2>$... val_<i = nextId()> <`= `init>?;
            ***/
            auto result = ctx.insertFunctionAllocation(alloc);
            if (!result)
                return result.error();

            /***
            val_<i>.data
            ***/
            return c::arrayData(valName);
        }

        esl::result<std::vector<std::string>> arrayTypeNames (type::Array const & type) {
            return esl::unite_results(
                esl::lift<esl::target::component_vector, esl::target::category>(interface::typeName)(type.type)
            );
        }

        // TODO: Not used yet.
        bool arrayTypesConst (type::Array const & type) {
            return esl::all(esl::lift<esl::target::component_vector, esl::target::category>(
                [] (type::Const const &) {
                    return true;
                },
                // TODO: Or any of the implicitly const types. (Which might be irrelevant for arrays though...)
                [] (auto const &) {
                    return false;
                }
            )(type.type));
        }

        interface::DefinitionTranslationResult translateArrayDefinition (
            context::C & ctx,
            bool constant,
            type::Array const & type,
            std::optional<std::string> const & definition
        ) {
            auto typeNamesResult = arrayTypeNames(type);
            if (!typeNamesResult)
                return typeNamesResult.error();
            auto typeNames = *typeNamesResult;

            auto types   = c::templateArguments(typeNames);
            auto size    = std::to_string(type.size);
            auto varName = c::variableName(std::to_string(ctx.nextId()));
            auto ptrType = constant
                ? c::constArrayPointerType(types)
                : c::arrayPointerType(types);

            if (definition) {
                auto local = c::statement(c::definition(ptrType, varName, *definition));

                /***
                local:
                struct cth_tup$<type1>$<type2>$... * <`const`>? var_<j = nextId()> = <definition>;
                ***/
                auto result = ctx.insertStatement(local);
                if (!result)
                    return result.error();

            } else {
                /***
                function scope:
                struct cth_arr$<size>$<type1>$<type2>$... val_<i = nextId()> = {0};
                ***/
                auto allocatedResult = translateArrayAllocation(ctx, c::zeroInit(), size, types);
                if (!allocatedResult)
                    return allocatedResult.error();

                auto local = c::statement(c::definition(ptrType, varName, *allocatedResult));

                /***
                local:
                struct cth_tup$<type1>$<type2>$... * <`const`>? var_<j = nextId()> = val_<i>.data;
                ***/
                auto result = ctx.insertStatement(local);
                if (!result)
                    return result.error();
            }

            /***
            var_<j>
            ***/
            return varName;
        };

    }

    //// Bool ////

    interface::DisplayResult type::Bool::display () const {
        return "Bool";
    }

    interface::SameTypeResult type::Bool::sameType (type::Bool const &) const {
        return true;
    }

    interface::CommonTypeResult type::Bool::commonType (type::Bool const &) const {
        return {type::Bool{}};
    }

    interface::CommonTypeResult type::Bool::commonType (type::Int const &) const {
        return {type::Int{}};
    }

    interface::CommonTypeResult type::Bool::commonType (type::Float const &) const {
        return {type::Float{}};
    }

    interface::CommonTypeResult type::Bool::commonType (type::In const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(interface::commonType)(*this, other.type);
    }

    interface::CommonTypeResult type::Bool::commonType (type::Const const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(interface::commonType)(*this, other.type);
    }

    interface::DefinitionTranslationResult type::Bool::translateDefinition (
        context::C & ctx,
        std::optional<std::string> const & definition,
        bool
    ) const {
        return translateSimpleDefinition(ctx, definition, type::Bool::directTypeName);
    }

    //// Int ////

    interface::DisplayResult type::Int::display () const {
        return "Int";
    }

    interface::SameTypeResult type::Int::sameType (type::Int const &) const {
        return true;
    }

    interface::CommonTypeResult type::Int::commonType (type::Int const &) const {
        return {type::Int{}};
    }

    interface::CommonTypeResult type::Int::commonType (type::Float const &) const {
        return {type::Float{}};
    }

    interface::CommonTypeResult type::Int::commonType (type::In const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(interface::commonType)(*this, other.type);
    }

    interface::CommonTypeResult type::Int::commonType (type::Const const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(interface::commonType)(*this, other.type);
    }

    interface::DefinitionTranslationResult type::Int::translateDefinition (
        context::C & ctx,
        std::optional<std::string> const & definition,
        bool
    ) const {
        return translateSimpleDefinition(ctx, definition, type::Int::directTypeName);
    }

    //// Float ////

    interface::DisplayResult type::Float::display () const {
        return "Float";
    }

    interface::SameTypeResult type::Float::sameType (type::Float const &) const {
        return true;
    }

    interface::CommonTypeResult type::Float::commonType (type::Float const &) const {
        return {type::Float{}};
    }

    interface::CommonTypeResult type::Float::commonType (type::In const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(interface::commonType)(*this, other.type);
    }

    interface::CommonTypeResult type::Float::commonType (type::Const const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(interface::commonType)(*this, other.type);
    }

    interface::DefinitionTranslationResult type::Float::translateDefinition (
        context::C & ctx,
        std::optional<std::string> const & definition,
        bool
    ) const {
        return translateSimpleDefinition(ctx, definition, type::Float::directTypeName);
    }

    //// String ////

    interface::DisplayResult type::String::display () const {
        return "String";
    }

    interface::SameTypeResult type::String::sameType (type::String const &) const {
        return true;
    }

    interface::CommonTypeResult type::String::commonType (type::String const &) const {
        return {type::String{}};
    }

    interface::DefinitionTranslationResult type::String::translateDefinition (
        context::C &,
        std::optional<std::string> const &,
        bool
    ) const {
        return esl::result_error{"Strings are not implemented yet."};
    }

    //// In ////

    interface::DisplayResult type::In::display () const {
        return "T in"; // TODO
    }

    /*
    interface::TypeDecayResult type::In::decayType () const {
        return *type;
    }
    */

    interface::SameTypeResult type::In::sameType (type::In const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(interface::sameTypes)(type, other.type);
    }

    interface::TypeCompletionResult type::IncompleteIn::completeType (context::Cynth & ctx) const {
        auto result = esl::lift<esl::target::component, esl::target::category>(interface::completeType(ctx))(type);
        if (!result)
            return result.error();
        return {type::In{{
            .type = *result
        }}};
    }

    interface::DefinitionTranslationResult type::In::translateDefinition (
        context::C & ctx,
        std::optional<std::string> const & definition,
        bool
    ) const {
        auto typeNameResult = esl::lift<esl::target::component, esl::target::category>(interface::directTypeName)(type);
        if (!typeNameResult)
            return typeNameResult.error();

        auto type    = c::typeName(*typeNameResult);
        auto varType = c::inputPointerType(type);
        auto varName = c::variableName(std::to_string(ctx.nextId()));

        if (definition) {
            auto local = c::definition(varType, varName, *definition);

            /***
            local:
            cth_<type> volatile * var_<j = nextId()> = <definition>;
            ***/
            auto result = ctx.insertStatement(local);
            if (!result)
                return result.error();

        } else {
            auto valType = c::inputValueType(type);
            auto valName = c::inputValueName(std::to_string(ctx.nextId()));
            auto alloc   = c::declaration(valType, valName);
            auto local   = c::definition(varType, varName, c::addressof(valName));

            /***
            global:
            cth_<type> volatile cth_inval_<i = nextId()>;
            local:
            cth_<type> volatile * var_<j = nextId()> = &cth_inval_<i>;
            ***/
            auto result = esl::chain_results(
                [&ctx, &alloc] { return ctx.insertStaticAllocation(alloc); },
                [&ctx, &local] { return ctx.insertStatement(local); }
            );
            if (!result)
                return result.error();
        }

        /***
        var_<j>
        ***/
        return varName;
    }

    //// Out ////

    interface::DisplayResult type::Out::display () const {
        return "T out"; // TODO
    }

    /*
    interface::TypeDecayResult type::Out::decayType () const {
        return *type;
    }
    */

    interface::SameTypeResult type::Out::sameType (type::Out const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(interface::sameTypes)(type, other.type);
    }

    interface::TypeCompletionResult type::IncompleteOut::completeType (context::Cynth & ctx) const {
        auto result = esl::lift<esl::target::component, esl::target::category>(interface::completeType(ctx))(type);
        if (!result)
            return result.error();
        return {type::Out{{
            .type = *result
        }}};
    }

    interface::DefinitionTranslationResult type::Out::translateDefinition (
        context::C & ctx,
        std::optional<std::string> const & definition,
        bool
    ) const {
        auto typeNameResult = esl::lift<esl::target::component, esl::target::category>(interface::directTypeName)(type);
        if (!typeNameResult)
            return typeNameResult.error();

        auto type    = c::typeName(*typeNameResult);
        auto valType = c::outputValueType(type);
        auto valName = c::outputValueName(std::to_string(ctx.nextId()));
        auto varType = c::outputPointerType(valType);
        auto varName = c::variableName(std::to_string(ctx.nextId()));

        if (definition) {
            auto local = c::definition(varType, varName, *definition);

            /***
            local:
            cth_<type> * var_<j = nextId()> = <definition>;
            ***/
            auto result = ctx.insertStatement(local);
            if (!result)
                return result.error();

        } else {

            auto alloc = c::declaration(valType, valName);
            auto local = c::definition(varType, varName, c::addressof(valName));

            /***
            global:
            cth_<type> cth_outval_<i = nextId()>;
            local:
            cth_<type> * var_<j = nextId()> = &cth_outval_<i>;
            ***/
            auto result = esl::chain_results(
                [&ctx, &alloc] { return ctx.insertStaticAllocation(alloc); },
                [&ctx, &local] { return ctx.insertStatement(local); }
            );
            if (!result)
                return result.error();
        }

        /***
        var_<j>
        ***/
        return varName;
    }

    //// Const ////

    interface::DisplayResult type::Const::display () const {
        return "T const"; // TODO
    }

    // TODO: This should be somehow linked with the strings configured in sem/translation.hpp
    /** `T_const` */
    interface::TypeNameResult type::Const::typeName () const {
        auto result = esl::lift<esl::target::component, esl::target::category>(interface::typeName)(type);
        if (!result)
            return result.error();
        return *result + "_const";
    }

    /*
    interface::TypeDecayResult type::Const::decayType () const {
        return *type;
    }
    */

    interface::SameTypeResult type::Const::sameType (type::Const const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(interface::sameTypes)(type, other.type);
    }

    interface::CommonTypeResult type::Const::commonType (type::Const const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(interface::commonType)(type, other.type);
        /*
        auto result = esl::lift<esl::target::component, esl::target::category>(interface::commonType)(type, other.type);
        if (!result)
            return result.error();
        return {type::Const{{
            .type = *result
        }}};
        */
    }

    interface::CommonTypeResult type::Const::commonType (type::Array const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(
            [&other] (type::Array const & a) -> esl::result<CompleteType> {
                return a.commonType(other);
            },
            [] (auto const & a) -> esl::result<CompleteType> {
                return esl::result_error{"Non-array const type does not have a common type with an array type."};
            }
        )(type);
    }

    interface::TypeCompletionResult type::IncompleteConst::completeType (context::Cynth & ctx) const {
        auto result = esl::lift<esl::target::component, esl::target::category>(interface::completeType(ctx))(type);
        if (!result)
            return result.error();
        return {type::Const{{
            .type = *result
        }}};
    }

    interface::DefinitionTranslationResult type::Const::translateDefinition (
        context::C & ctx,
        std::optional<std::string> const & definition,
        bool compval
    ) const {
        if (compval) return {}; // Skip compconst values.
        return esl::lift<esl::target::component, esl::target::category>(
            [&ctx, &definition] (type::Array const & type) -> interface::DefinitionTranslationResult {
                /***
                struct cth_tup$<type1>$<type2>$... * const var_<nextId()> = <definition|allocated>;
                ***/
                return translateArrayDefinition(ctx, true, type, definition);
            },
            [&ctx, &definition] <interface::simpleType T> (T const &) -> interface::DefinitionTranslationResult {
                /***
                struct cth_<type>_const var_<nextId()> = <definition>;
                ***/
                return translateSimpleDefinition(ctx, definition, c::constType(T::directTypeName));
            },
            [] (auto const &) -> interface::DefinitionTranslationResult {
                return esl::result_error{"Only simple types and arrays may be marked const."};
            }
        )(type);
    }

    //// Array ////

    // TODO?
    esl::result<type::Array> type::Array::make (esl::component_vector<CompleteType> && type, sem::Integral size) {
        if (size <= 0)
            return esl::result_error{"Array must have a positive size."};
        auto elemTypeCheck =
            esl::unite_results(esl::lift<esl::target::component_vector, esl::target::category>(arrayElemTypeCheck)(type));
        if (!elemTypeCheck)
            return elemTypeCheck.error();
        return type::Array{{
            .type = std::move(type),
            .size = size
        }};
    }

    interface::DisplayResult type::Array::display () const {
        return "T [n]"; // TODO
    }

    interface::SameTypeResult type::Array::sameType (type::Array const & other) const {
        auto result = esl::lift<esl::target::component_vector, esl::target::category>(interface::sameTypes)(type, other.type);
        return result && size == other.size && esl::all(*result);
    }

    interface::CommonTypeResult type::Array::commonType (type::Array const & other) const {
        auto results = (esl::lift<esl::target::component_vector, esl::target::category>(
            [] <typename T, typename U> (T const & a, U const & b) -> std::optional<CompleteType> {
            //requires (std::sameType_as<T, U> || !std::sameType_as<T, type::Const> && std::sameType_as<U, type::Const>)
                if (interface::sameTypes(a, b))
                    return {a};
                return {};
            },
            [] <typename T> (type::Const const & a, T const & b) -> std::optional<CompleteType>
            requires (!std::same_as<T, type::Const>) {
                if (interface::sameTypes(a, b))
                    return {a};
                if (interface::sameTypes(a, type::Const{{.type = {b}}}))
                    return {type::Const{{a}}};
                return {};
            },
            [] <typename T> (T const & a, type::Const const & b) -> std::optional<CompleteType>
            requires (!std::same_as<T, type::Const>) {
                if (interface::sameTypes(a, b))
                    return {a};
                if (interface::sameTypes(type::Const{{.type = {a}}}, b))
                    return {type::Const{{.type = {a}}}};
                return {};
            }
        )(type, other.type));
        if (!results)
            return results.error();
        auto result = esl::unite_optionals(*results);
        if (!result)
            return esl::result_error{"No common type for two arrays because of mismatched elements type."};
        auto arrayResult = type::Array::make(
            esl::make_component_vector(*result),
            std::min(size, other.size)
        );
        if (!arrayResult)
            return arrayResult.error();
        return {*arrayResult};
    }

    interface::TypeCompletionResult type::IncompleteArray::completeType (context::Cynth & ctx) const {
        auto typeResult = esl::unite_results(
            esl::lift<esl::target::component_vector, esl::target::category>(interface::completeType(ctx))(type)
        );
        if (!typeResult)
            return typeResult.error();

        auto sizeResult = esl::lift<esl::target::component, esl::target::category>(
            [] (value::Unknown const &) -> esl::result<int> {
                return esl::result_error{"Unknown array size."};
            },
            [&ctx] <interface::value Value> (Value const & value) -> esl::result<int> {
                auto x = interface::convertValue(ctx)(value, type::Int{});
                ESL_INSPECT(x);
                return esl::lift<esl::target::result, esl::target::category>(interface::get<sem::Integral>)(
                    interface::convertValue(ctx)(value, type::Int{})
                );
            }
        )(size);
        if (!sizeResult)
            return sizeResult.error();

        auto arrayResult = type::Array::make(
            esl::make_component_vector(*typeResult),
            *sizeResult
        );
        if (!arrayResult)
            return arrayResult.error();
        return {*arrayResult};
    }

    interface::DefinitionTranslationResult type::Array::translateDefinition (
        context::C & ctx,
        std::optional<std::string> const & definition,
        bool
    ) const {
        return translateArrayDefinition(ctx, false, *this, definition);
    }

    interface::AllocationTranslationResult type::Array::translateAllocation (
        context::C & ctx,
        std::optional<std::string> const & initialization
    ) const {
        // TODO: compval?
        auto typeNamesResult = arrayTypeNames(*this);
        if (!typeNamesResult)
            return typeNamesResult.error();
        auto typeNames = *typeNamesResult;
        auto types = c::templateArguments(typeNames);
        return translateArrayAllocation(ctx, initialization, std::to_string(size), types);
    }

    //// Buffer ////

    esl::result<type::Buffer> type::Buffer::make (sem::Integral size) {
        if (size <= 0)
            return esl::result_error{"Buffer must have a positive size."};
        return type::Buffer{{
            .size = size
        }};
    }

    interface::DisplayResult type::Buffer::display () const {
        return "buffer [n]"; // TODO
    }

    interface::CommonTypeResult type::Buffer::commonType (type::Buffer const & other) const {
        if (size != other.size)
            return esl::result_error{"No common type for two buffers because of different sizes."};
        return {*this};
    }

    interface::SameTypeResult type::Buffer::sameType (type::Buffer const & other) const {
        return size == other.size;
    }

    interface::TypeCompletionResult type::IncompleteBuffer::completeType (context::Cynth & ctx) const {
        auto sizeResult = esl::lift<esl::target::component, esl::target::category>(
            [] (value::Unknown const &) -> esl::result<sem::Integral> {
                return esl::result_error{"Unknown array size."};
            },
            [&ctx] <interface::value Value> (Value const & value) -> esl::result<sem::Integral> {
                return esl::lift<esl::target::result, esl::target::category>(interface::get<sem::Integral>)(
                    interface::convertValue(ctx)(value, type::Int{})
                );
            }
        )(size);
        if (!sizeResult)
            return sizeResult.error();

        auto bufferResult = type::Buffer::make(*sizeResult);
        if (!bufferResult)
            return bufferResult.error();

        return {*bufferResult};
    }

    namespace {

        enum struct BufferKind {
            internal,
            input,
            output
        };

        std::string bufferValueName (
            BufferKind kind,
            std::string const & id
        ) {
            switch (kind) {
            case BufferKind::internal:
                return c::bufferValueName(id);
            case BufferKind::input:
                return c::inputBufferValueName(id);
            case BufferKind::output:
                return c::outputBufferValueName(id);
            }
        }

        esl::result<std::string> translateBufferAllocation (
            context::C & ctx,
            BufferKind kind,
            type::Buffer const & type
        ) {
            auto valType = c::bufferValueType(std::to_string(type.size));
            auto valName = bufferValueName(kind, std::to_string(ctx.nextId()));
            auto alloc   = c::declaration(valType, valName);

            /***
            global:
            struct cth_buff$<size> cth_<buff = `buffval`|`inbuffval`|`outbuffval`>_<i = nextId()>;
            ***/
            auto allocatedResult = ctx.insertStaticAllocation(alloc);

            /***
            cth_<buff>_<i>.data;
            ***/
            return c::bufferData(valName);
        }

    }

    interface::DefinitionTranslationResult type::Buffer::translateDefinition (
        context::C & ctx,
        std::optional<std::string> const & definition,
        bool
    ) const {
        if (!definition)
            return esl::result_error{"Buffers must be explicitly initialized."};

        auto varType = c::bufferPointerType();
        auto varName = c::variableName(std::to_string(ctx.nextId()));
        auto local   = c::definition(varType, varName, *definition);

        /***
        local:
        cth_float const * const var_<i = nextId()> = <definition>;
        ***/
        auto result = ctx.insertStatement(local);
        if (!result)
            return result.error();

        /***
        var_<i>
        ***/
        return varName;
    }

    //// Function ////

    interface::DisplayResult type::Function::display () const {
        return "Output (Input)"; // TODO
    }

    interface::CommonTypeResult type::Function::commonType (type::Function const & other) const {
        auto outResult = esl::lift<esl::target::component_vector, esl::target::category>(interface::sameTypes)(out, other.out);
        if (!outResult)
            return outResult.error();
        if (!esl::all(*outResult))
            return esl::result_error{"No common type for two functions because of diferent output types."};
        auto inResult = esl::lift<esl::target::component_vector, esl::target::category>(interface::sameTypes)(in, other.in);
        if (!inResult)
            return inResult.error();
        if (!esl::all(*inResult))
            return esl::result_error{"No common type for two functions because of diferent input types."};
        return {*this};
    }

    interface::SameTypeResult type::Function::sameType (type::Function const & other) const {
        auto outResult = esl::lift<esl::target::component_vector, esl::target::category>(interface::sameTypes)(out, other.out);
        auto inResult = esl::lift<esl::target::component_vector, esl::target::category>(interface::sameTypes)(in, other.in);
        return
            outResult && esl::all(*outResult) &&
            inResult  && esl::all(*inResult);
    }

    interface::TypeCompletionResult type::IncompleteFunction::completeType (context::Cynth & ctx) const {
        auto outResult = esl::unite_results(
            esl::lift<esl::target::component_vector, esl::target::category>(interface::completeType(ctx))(out)
        );
        if (!outResult)
            return outResult.error();
        auto inResult = esl::unite_results(
            esl::lift<esl::target::component_vector, esl::target::category>(interface::completeType(ctx))(in)
        );
        if (!inResult)
            return inResult.error();
        return {type::Function{{
            .out = esl::make_component_vector(*outResult),
            .in  = esl::make_component_vector(*inResult)
        }}};
    }

    namespace {

        // TODO: Function "allocation".

    }

    interface::DefinitionTranslationResult type::Function::translateDefinition (
        context::C & ctx,
        std::optional<std::string> const & definition,
        bool compval
    ) const {
        // TODO: Can I really skip declating the contexts?
        // Inserting the compconst function value would need to handle declaring the context in-place as a literal constant.
        if (compval) return {}; // Skip compconst values.

        if (!definition)
            return esl::result_error{"Functions must be initialized explicitly."};

        auto varType = c::infer(*definition);
        auto varName = c::contextVariableName(std::to_string(ctx.nextId()));
        auto local   = c::definition(varType, varName, *definition);

        /***
        local:
        typeof(<definition>) ctxvar_<nextId()> = <definition>;
        ***/
        auto result = ctx.insertStatement(local);
        if (!result)
            return result.error();

        return varName;
    }

#endif
}

namespace esl {

    using cynth::sem::CompleteType;
    using cynth::sem::IncompleteType;

    template <>
    void component_deleter<CompleteType>::operator () (CompleteType * ptr) const {
        delete ptr;
    }

    template <>
    CompleteType * component_allocator<CompleteType>::operator () (CompleteType const & other) const {
        return new CompleteType{other};
    }

    template <>
    CompleteType * component_allocator<CompleteType>::operator () (CompleteType && other) const {
        return new CompleteType{std::move(other)};
    }

    template <>
    void component_deleter<IncompleteType>::operator () (IncompleteType * ptr) const {
        delete ptr;
    }

    template <>
    IncompleteType * component_allocator<IncompleteType>::operator () (IncompleteType const & other) const {
        return new IncompleteType{other};
    }

    template <>
    IncompleteType * component_allocator<IncompleteType>::operator () (IncompleteType && other) const {
        return new IncompleteType{std::move(other)};
    }

}
