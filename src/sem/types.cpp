#include "sem/types.hpp"

#include <functional>
#include <optional>
#include <string>
#include <utility>

#include "esl/boolean.hpp"
#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/component.hpp"
#include "esl/containers.hpp"
#include "esl/functional.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/compound.hpp"
#include "sem/numeric_types.hpp"
#include "sem/values.hpp"

// TMP
#include "esl/debug.hpp"
#include "esl/macros.hpp"

namespace esl {

    using cynth::sem::CompleteType;
    using cynth::sem::IncompleteType;

    // Note: Some of these specializations are needed for the implementations below to work properly.
    // TODO: Maybe I should move it elsewhere. These specializations are only needed
    // for code that doesn't know about complete definitions of these types.
    // However, code in any of the implementation files can include the full definitions,
    // and so the default specializations can be used instead.

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

namespace cynth::sem {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DefinitionProcessingResult;
    using interface::DisplayResult;
    using interface::SameTypeResult;
    using interface::TypeSpecifierTranslationResult;
    using interface::TypeTranslationResult;
    using sem::Variable;
    using sem::CompleteValue;
    using sem::TypedExpression;
    using sem::TypedName;

    namespace {

        // The following helper functions are defined at the bottom of this file.

        template <typename Type>
        DefinitionProcessingResult processSimpleDefinition (
            context::Main &,
            Type const &,
            std::optional<ResolvedValue> const &
        );

    }

    //// Bool ////

    DisplayResult type::Bool::display () const {
        return "Bool";
    }

    SameTypeResult type::Bool::sameType (type::Bool const &) const {
        return true;
    }

    DefinitionProcessingResult type::Bool::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> const & definition
    ) const {
        return processSimpleDefinition(ctx, *this, definition);
    }

    //// Int ////

    DisplayResult type::Int::display () const {
        return "Int";
    }

    SameTypeResult type::Int::sameType (type::Int const &) const {
        return true;
    }

    DefinitionProcessingResult type::Int::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> const & definition
    ) const {
        return processSimpleDefinition(ctx, *this, definition);
    }

    //// Float ////

    DisplayResult type::Float::display () const {
        return "Float";
    }

    SameTypeResult type::Float::sameType (type::Float const &) const {
        return true;
    }

    DefinitionProcessingResult type::Float::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> const & definition
    ) const {
        return processSimpleDefinition(ctx, *this, definition);
    }

    //// String ////

    DisplayResult type::String::display () const {
        return "String";
    }

    SameTypeResult type::String::sameType (type::String const &) const {
        return true;
    }

    DefinitionProcessingResult type::String::processDefinition (
        context::Main &,
        std::optional<ResolvedValue> const &
    ) const {
        return esl::result_error{"Strings are not implemented yet."};
    }

    //// In ////

    DisplayResult type::In::display () const {
        return (interface::display || target::category{} <<= *type) + " in";
    }

    SameTypeResult type::In::sameType (type::In const & other) const {
        return interface::sameTypes || target::category{} <<= args(*type, *other.type);
    }

    DefinitionProcessingResult type::In::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> const & definition
    ) const {
        auto valueType = *type;
        if (!definition) {
            // No definiton => Allocating a new value:
            return [&] (auto && typeName) -> DefinitionProcessingResult {
                auto type    = c::global(std::move(typeName));
                auto varType = c::inputPointerType(type);
                auto varName = c::variableName(c::id(ctx.nextId()));
                auto valType = c::inputType(type);
                auto valName = c::inputValueName(std::to_string(ctx.nextId()));
                auto alloc   = c::declaration(valType, valName);
                auto local   = c::definition(varType, varName, c::addressof(valName));

                /***
                global:
                cth_<type> <val>;
                local:
                cth_<type> * <var> = &<val>;
                ***/
                ctx.global.insertAllocation(alloc);
                ctx.insertStatement(local);

                return Variable{CompleteValue{sem::value::In{valName, *this}}};

            } || target::result{} <<= interface::typeName || target::category{} <<= valueType;
        }

        // Creating a reference to an existing value:
        return [&] (CompleteValue definition) -> DefinitionProcessingResult { // TODO: Why don't rvalued parameters work here?
            // From comp-time reference => compconst variable:
            auto fromType = interface::valueType || target::category{} <<= definition;
            // Note: There will be no implicit conversions in the first version.
            if (!(interface::sameType(*this) || target::category{} <<= fromType))
                return esl::result_error{"Initializing from an incompatible type."};

            return Variable{definition};

        } | [&] (TypedExpression definition) -> DefinitionProcessingResult {
            // From run-time reference => run-time (const) variable:
            auto fromType = definition.type;
            // Note: There will be no implicit conversions in the first version.
            if (!(interface::sameType(*this) || target::category{} <<= fromType))
                return esl::result_error{"Initializing from an incompatible type."};

            return [&] (auto && typeName) -> DefinitionProcessingResult {
                auto type    = c::global(std::move(typeName));
                auto varType = c::inputPointerType(type);
                auto varName = c::variableName(c::id(ctx.nextId()));
                auto local   = c::definition(varType, varName, definition.expression);

                /***
                local:
                cth_<type> * <var> = <definition>;
                ***/
                ctx.insertStatement(local);

                /***
                <var>
                ***/
                return Variable{TypedName{*this, varName}};

            } || target::result{} <<= interface::typeName || target::category{} <<= valueType;

        } || target::category{} <<= *std::move(definition);
    }

#if 0
    //// Out ////

    DisplayResult type::Out::display () const {
        return "T out"; // TODO
    }

    /*
    TypeDecayResult type::Out::decayType () const {
        return *type;
    }
    */

    SameTypeResult type::Out::sameType (type::Out const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(interface::sameTypes)(type, other.type);
    }

    DefinitionProcessingResult type::Out::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> const & definition
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

    DisplayResult type::Const::display () const {
        return "T const"; // TODO
    }

    // TODO: This should be somehow linked with the strings configured in sem/translation.hpp
    /** `T_const` */
    TypeNameResult type::Const::typeName () const {
        auto result = esl::lift<esl::target::component, esl::target::category>(interface::typeName)(type);
        if (!result)
            return result.error();
        return *result + "_const";
    }

    /*
    TypeDecayResult type::Const::decayType () const {
        return *type;
    }
    */

    SameTypeResult type::Const::sameType (type::Const const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(interface::sameTypes)(type, other.type);
    }

    DefinitionProcessingResult type::Const::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> const & definition
    ) const {
        if (compval) return {}; // Skip compconst values.
        return esl::lift<esl::target::component, esl::target::category>(
            [&ctx, &definition] (type::Array const & type) -> DefinitionProcessingResult {
                /***
                struct cth_tup$<type1>$<type2>$... * const var_<nextId()> = <definition|allocated>;
                ***/
                return translateArrayDefinition(ctx, true, type, definition);
            },
            [&ctx, &definition] <interface::simpleType T> (T const &) -> DefinitionProcessingResult {
                /***
                struct cth_<type>_const var_<nextId()> = <definition>;
                ***/
                return processSimpleDefinition(ctx, definition, c::constType(T::directTypeName));
            },
            [] (auto const &) -> DefinitionProcessingResult {
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

    DisplayResult type::Array::display () const {
        return "T [n]"; // TODO
    }

    SameTypeResult type::Array::sameType (type::Array const & other) const {
        auto result = esl::lift<esl::target::component_vector, esl::target::category>(interface::sameTypes)(type, other.type);
        return result && size == other.size && esl::all(*result);
    }

    DefinitionProcessingResult type::Array::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> const & definition
    ) const {
        return translateArrayDefinition(ctx, false, *this, definition);
    }

    AllocationTranslationResult type::Array::translateAllocation (
        context::Main & ctx,
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

    DisplayResult type::Buffer::display () const {
        return "buffer [n]"; // TODO
    }

    SameTypeResult type::Buffer::sameType (type::Buffer const & other) const {
        return size == other.size;
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
            context::Main & ctx,
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

    DefinitionProcessingResult type::Buffer::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> const & definition
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

    DisplayResult type::Function::display () const {
        return "Output (Input)"; // TODO
    }

    SameTypeResult type::Function::sameType (type::Function const & other) const {
        auto outResult = esl::lift<esl::target::component_vector, esl::target::category>(interface::sameTypes)(out, other.out);
        auto inResult = esl::lift<esl::target::component_vector, esl::target::category>(interface::sameTypes)(in, other.in);
        return
            outResult && esl::all(*outResult) &&
            inResult  && esl::all(*inResult);
    }

    namespace {

        // TODO: Function "allocation".

    }

    DefinitionProcessingResult type::Function::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> const & definition
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

#if 0 // TODO
    namespace {

        template <typename... Ts>
        AllocationTranslationResult translateArrayAllocation (
            context::Main & ctx,
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

        DefinitionProcessingResult translateArrayDefinition (
            context::Main & ctx,
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
#endif

    // Implementing the heper functions defined at the top of this file:

    namespace {

        DefinitionProcessingResult runtimeSimpleDefinition (
            context::Main      & ctx,
            CompleteType const & type,
            std::string  const & typeName,
            std::string  const & definition
        ) {
            auto varName  = c::variableName(c::id(ctx.nextId()));
            auto local    = c::definition(c::global(typeName), varName, definition);

            /***
            local:
            cth_<type> <var> = <definition>;
            ***/
            ctx.insertStatement(local);

            /***
            var_<i>
            ***/
            return Variable{TypedName{type, varName}};
        }

        template <typename Type>
        DefinitionProcessingResult processSimpleDefinition (
            context::Main                      & ctx,
            Type                         const & type,
            std::optional<ResolvedValue> const & optDef
        ) {
            if (type.constant && !optDef)
                return esl::result_error{"A constant variable must be explicitly initialized."};

            auto definition = optDef ? *optDef : ResolvedValue{TypedExpression{type, Type::defaultExpression()}};

            return [&] (CompleteValue && definition) -> DefinitionProcessingResult {
                auto valueType = interface::valueType || target::category{} <<= definition;
                // Note: There will be no implicit conversions in the first version.
                if (!(interface::sameType(type) || target::category{} <<= valueType))
                    return esl::result_error{"Initializing from an incompatible type."};

                if (type.constant) {
                    // Comp-const variable:
                    return Variable{definition};
                }

                // Run-time const variable:
                return [&] (TypedExpression && definition) -> DefinitionProcessingResult {
                    return runtimeSimpleDefinition(ctx, type, Type::typeName, definition.expression);

                } || target::result{} <<= interface::translateValue(ctx) || target::category{} <<= std::move(definition);

            } | [&] (TypedExpression && definition) -> DefinitionProcessingResult {
                return runtimeSimpleDefinition(ctx, type, Type::typeName, definition.expression);

            } || target::category{} <<= std::move(definition);
        }

    }

}
