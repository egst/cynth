#include "sem/types.hpp"

#include <functional> // TODO: is this still needed?
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
#include "interface/compound.hpp"
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
            context::Main                & ctx,
            Type                   const & type,
            std::optional<ResolvedValue> & optDef
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

    //// Bool ////

    DisplayResult type::Bool::display () const {
        return std::string{} + "Bool" + (constant ? " const" : "");
    }

    TypeTranslationResult type::Bool::translateType () const {
        auto name = c::booleanType();
        return constant ? c::constness(name) : name;
    }

    TypeSpecifierTranslationResult type::Bool::translateTypeSpecifier () const {
        return tpl::TypeSpecifier{
            .type     = c::booleanType(),
            .constant = constant
        };
    }

    SameTypeResult type::Bool::sameType (type::Bool const &) const {
        return true;
    }

    SameTypeResult type::Bool::identicalType (type::Bool const & other) const {
        return constant == other.constant;
    }

    void type::Bool::loseConstness () {
        constant = false;
    }

    DefinitionProcessingResult type::Bool::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> & definition
    ) const {
        return processSimpleDefinition(ctx, *this, definition);
    }

    //// Int ////

    DisplayResult type::Int::display () const {
        return std::string{} + "Int" + (constant ? " const" : "");
    }

    TypeTranslationResult type::Int::translateType () const {
        auto name = c::integralType();
        return constant ? c::constness(name) : name;
    }

    TypeSpecifierTranslationResult type::Int::translateTypeSpecifier () const {
        return tpl::TypeSpecifier{
            .type     = c::integralType(),
            .constant = constant
        };
    }

    SameTypeResult type::Int::sameType (type::Int const &) const {
        return true;
    }

    SameTypeResult type::Int::identicalType (type::Int const & other) const {
        return constant == other.constant;
    }

    void type::Int::loseConstness () {
        constant = false;
    }

    DefinitionProcessingResult type::Int::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> & definition
    ) const {
        return processSimpleDefinition(ctx, *this, definition);
    }

    //// Float ////

    DisplayResult type::Float::display () const {
        return std::string{} + "Float" + (constant ? " const" : "");
    }

    TypeTranslationResult type::Float::translateType () const {
        auto name = c::floatingType();
        return constant ? c::constness(name) : name;
    }

    TypeSpecifierTranslationResult type::Float::translateTypeSpecifier () const {
        return tpl::TypeSpecifier{
            .type     = c::floatingType(),
            .constant = constant
        };
    }

    SameTypeResult type::Float::sameType (type::Float const &) const {
        return true;
    }

    SameTypeResult type::Float::identicalType (type::Float const & other) const {
        return constant == other.constant;
    }

    void type::Float::loseConstness () {
        constant = false;
    }

    DefinitionProcessingResult type::Float::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> & definition
    ) const {
        return processSimpleDefinition(ctx, *this, definition);
    }

    //// String ////

    DisplayResult type::String::display () const {
        return "String";
    }

    TypeTranslationResult type::String::translateType () const {
        return "cth_str"; // Not implemented.
    }

    TypeSpecifierTranslationResult type::String::translateTypeSpecifier () const {
        // Not implemented.
        return tpl::TypeSpecifier{
            .type     = "cth_str",
            .constant = true
        };
    }

    SameTypeResult type::String::sameType (type::String const &) const {
        return true; // Not implemented.
    }

    SameTypeResult type::String::identicalType (type::String const & other) const {
        return sameType(other);
    }

    DefinitionProcessingResult type::String::processDefinition (
        context::Main &,
        std::optional<ResolvedValue> &
    ) const {
        return esl::result_error{"Strings are not implemented yet."};
    }

    //// In ////

    DisplayResult type::In::display () const {
        return (interface::display || target::category{} <<= *type) + " in";
    }

    TypeTranslationResult type::In::translateType () const {
        // This assumes that the nested type can only be simple, and so will always be translatable.
        auto nested = *(interface::translateType || target::category{} <<= *type);
        return c::inputPointerType(nested);
    }

    TypeSpecifierTranslationResult type::In::translateTypeSpecifier () const {
        // This assumes that the nested type can only be simple, and so will always be translatable.
        auto nested = *(interface::translateType || target::category{} <<= *type);
        return tpl::TypeSpecifier{
            .type    = nested,
            .pointer = true
        };
    }

    SameTypeResult type::In::sameType (type::In const & other) const {
        return interface::sameTypes || target::category{} <<= args(*type, *other.type);
    }

    SameTypeResult type::In::identicalType (type::In const & other) const {
        return sameType(other);
    }

    DefinitionProcessingResult type::In::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> & definition
    ) const {
        auto valueType = *type;
        if (!definition) {
            // No definiton => Allocating a new value:
            return [&] (auto typeName) -> DefinitionProcessingResult {
                auto varType = c::inputPointerType(typeName);
                auto varName = c::variableName(c::id(ctx.nextId()));
                auto valType = c::inputType(typeName);
                auto valName = c::inputValueName(std::to_string(ctx.nextId()));
                auto alloc   = c::declaration(valType, valName);
                auto local   = c::definition(varType, varName, c::addressof(valName));

                /***
                global:
                <type> <val>;
                local:
                <type> const * <var> = &<val>;
                ***/
                ctx.global.insertAllocation(alloc);
                ctx.insertStatement(local);

                return Variable{CompleteValue{sem::value::In{valName, *this}}};

            } || target::result{} <<= interface::translateType || target::category{} <<= valueType;
        }

        // Creating a reference to an existing value:
        return [&] (CompleteValue const & definition) -> DefinitionProcessingResult { // TODO: Why don't rvalued parameters work here?
            // From comp-time reference => compconst variable:
            auto fromType = interface::valueType || target::category{} <<= definition;
            // Note: There will be no implicit conversions in the first version.
            if (!(interface::sameType(*this) || target::category{} <<= fromType))
                return esl::result_error{"Initializing from an incompatible type."};

            return Variable{definition};

        } | [&] (TypedExpression const & definition) -> DefinitionProcessingResult {
            // From run-time reference => run-time (const) variable:
            auto fromType = definition.type;
            // Note: There will be no implicit conversions in the first version.
            if (!(interface::sameType(*this) || target::category{} <<= fromType))
                return esl::result_error{"Initializing from an incompatible type."};

            return [&] (auto typeName) -> DefinitionProcessingResult {
                auto varType = c::inputPointerType(typeName);
                auto varName = c::variableName(c::id(ctx.nextId()));
                auto local   = c::definition(varType, varName, definition.expression);

                /***
                local:
                <type> const * <var> = <definition>;
                ***/
                ctx.insertStatement(local);

                /***
                <var>
                ***/
                return Variable{TypedName{*this, varName}};

            } || target::result{} <<= interface::translateType || target::category{} <<= valueType;

        } || target::category{} <<= *definition;
    }

    //// Out ////

    DisplayResult type::Out::display () const {
        return (interface::display || target::category{} <<= *type) + " out";
    }

    TypeSpecifierTranslationResult type::Out::translateTypeSpecifier () const {
        // This assumes that the nested type can only be simple, and so will always be translatable.
        auto nested = *(interface::translateType || target::category{} <<= *type);
        return tpl::TypeSpecifier{
            .type     = nested,
            .constant = true,
            .constptr = true
        };
    }

    TypeTranslationResult type::Out::translateType () const {
        // This assumes that the nested type can only be simple, and so will always be translatable.
        auto nested = *(interface::translateType || target::category{} <<= *type);
        return c::outputPointerType(nested);
    }

    SameTypeResult type::Out::sameType (type::Out const & other) const {
        return interface::sameTypes || target::category{} <<= args(*type, *other.type);
    }

    SameTypeResult type::Out::identicalType (type::Out const & other) const {
        return sameType(other);
    }

    DefinitionProcessingResult type::Out::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> & definition
    ) const {
        auto valueType = *type;
        if (!definition) {
            // No definiton => Allocating a new value:
            return [&] (auto typeName) -> DefinitionProcessingResult {
                auto varType = c::outputPointerType(typeName);
                auto varName = c::variableName(c::id(ctx.nextId()));
                auto valType = c::outputType(typeName);
                auto valName = c::outputValueName(std::to_string(ctx.nextId()));
                auto alloc   = c::declaration(valType, valName);
                auto local   = c::definition(varType, varName, c::addressof(valName));

                /***
                global:
                <type> <val>;
                local:
                <type> * <var> = &<val>;
                ***/
                ctx.global.insertAllocation(alloc);
                ctx.insertStatement(local);

                return Variable{CompleteValue{sem::value::Out{valName, *this}}};

            } || target::result{} <<= interface::translateType || target::category{} <<= valueType;
        }

        // Creating a reference to an existing value:
        return [&] (CompleteValue const & definition) -> DefinitionProcessingResult { // TODO: Why don't rvalued parameters work here?
            // From comp-time reference => compconst variable:
            auto fromType = interface::valueType || target::category{} <<= definition;
            // Note: There will be no implicit conversions in the first version.
            if (!(interface::sameType(*this) || target::category{} <<= fromType))
                return esl::result_error{"Initializing from an incompatible type."};

            return Variable{definition};

        } | [&] (TypedExpression const & definition) -> DefinitionProcessingResult {
            // From run-time reference => run-time (const) variable:
            auto fromType = definition.type;
            // Note: There will be no implicit conversions in the first version.
            if (!(interface::sameType(*this) || target::category{} <<= fromType))
                return esl::result_error{"Initializing from an incompatible type."};

            return [&] (auto typeName) -> DefinitionProcessingResult {
                auto varType = c::outputPointerType(typeName);
                auto varName = c::variableName(c::id(ctx.nextId()));
                auto local   = c::definition(varType, varName, definition.expression);

                /***
                local:
                <type> * <var> = <definition>;
                ***/
                ctx.insertStatement(local);

                /***
                <var>
                ***/
                return Variable{TypedName{*this, varName}};

            } || target::result{} <<= interface::translateType || target::category{} <<= valueType;

        } || target::category{} <<= *definition;
    }

    //// Array ////

    bool type::Array::constval () const {
        return interface::constant || target::category{} <<= *type;
    }

    DisplayResult type::Array::display () const {
        return
            (interface::display || target::category{} <<= *type) + (constval() ? " const" : "") +
            " [" + std::to_string(size) + "]" + (constant ? " const" : "");
    }

    TypeTranslationResult type::Array::translateType () const {
        // This assumes that the nested type can only be simple, and so will always be translatable.
        auto nested = *(interface::translateType || target::category{} <<= *type);
        return constant
            ? c::constness(c::pointer(nested))
            : c::pointer(nested);
    }

    TypeSpecifierTranslationResult type::Array::translateTypeSpecifier () const {
        // This assumes that the nested type can only be simple, and so will always be translatable.
        auto nested = *(interface::translateTypeSpecifier || target::category{} <<= *type);
        return tpl::TypeSpecifier{
            .type     = nested.type,
            .constant = nested.constant,
            .pointer  = !constant,
            .constptr = constant
        };
    }

    SameTypeResult type::Array::sameType (type::Array const & other) const {
        return
            (interface::identicalTypes || target::category{} <<= args(*type, *other.type)) &&
            size == other.size;
    }

    SameTypeResult type::Array::identicalType (type::Array const & other) const {
        return sameType(other) && constant == other.constant;
    }

    DefinitionProcessingResult type::Array::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> & definition
    ) const {

        if (definition) {
            // Referencing another value:
            return [&] (CompleteValue & definition) -> DefinitionProcessingResult {
                // Initializing from a comp-time value:
                return [&] (sem::value::Array & definition) -> DefinitionProcessingResult {
                    if (!interface::sameTypes(*this, definition.valueType))
                        return esl::result_error{"Initializing from an incompatible type."};

                    if (constant)
                        // Compconst reference variable:
                        return Variable{CompleteValue{sem::value::Array{definition.allocation, *this}}};

                    auto ptrType = translateType();
                    auto varName = c::variableName(c::id(ctx.nextId()));

                    // Run-time reference to run-time values:
                    return [&] (ArrayAllocation * alloc) -> DefinitionProcessingResult {
                        // From comp-time values:
                        auto valName = alloc->allocate(ctx);
                        auto local   = c::definition(ptrType, varName, valName);

                        /***
                        <type> * <var> = <val>;
                        ***/
                        ctx.insertStatement(local);

                        return Variable{TypedName{*this, varName}};

                    } | [&] (std::string const & alloc) -> DefinitionProcessingResult {
                        // From run-time values:
                        auto valName = alloc;
                        auto local   = c::definition(ptrType, varName, valName);

                        /***
                        <type> * <var> = <val>;
                        ***/
                        ctx.insertStatement(local);

                        return Variable{TypedName{*this, varName}};

                    } || target::variant{} <<= definition.allocation;

                } | [] (auto const &) -> DefinitionProcessingResult {
                    return esl::result_error{"Initializing from an incompatible type."};

                } || target::category{} <<= definition;

            } | [&] (TypedExpression const & definition) -> DefinitionProcessingResult {
                // Initializing from a run-time value:
                if (!(interface::sameType(*this) || target::category{} <<= definition.type))
                    return esl::result_error{"Initializing from an incompatible type."};
                auto ptrType = translateType();
                auto varName = c::variableName(c::id(ctx.nextId()));
                auto valName = definition.expression;
                auto local   = c::definition(ptrType, varName, valName);

                /***
                <type> * <var> = <val>;
                ***/
                ctx.insertStatement(local);

                return Variable{TypedName{*this, varName}};

            } || target::category{} <<= *definition;

        }

        // Allocating a new array value:

        return [&] (auto valueType) -> DefinitionProcessingResult {
            if (constval())
                return esl::result_error{"Const-valued arrays must be explicitly initialized."};

            auto arrayType = ctx.global.instantiate(tpl::Array{std::move(valueType), size});
            auto valName   = c::valueName(std::to_string(ctx.nextId()));
            auto alloc     = c::definition(arrayType, valName, c::zeroInitialization());

            /***
            function:
            cth_arr$<size>$<type> <val> = {0};
            ***/
            ctx.function.insertAllocation(alloc);

            if (constant)
                // Compconst reference:
                return Variable{CompleteValue{sem::value::Array{valName, *this}}};

            // Run-time reference:

            auto ptrType   = translateType();
            auto varName   = c::variableName(std::to_string(ctx.nextId()));
            auto local     = c::definition(ptrType, varName, valName);

            /***
            <type> * <var> = <val>;
            ***/
            ctx.insertStatement(local);

            return Variable{TypedName{*this, varName}};

        } || target::result{} <<= interface::translateTypeSpecifier || target::category{} <<= *type;
    }

    //// Buffer ////

    DisplayResult type::Buffer::display () const {
        return "buffer [" + std::to_string(size) + "]";
    }

    TypeTranslationResult type::Buffer::translateType () const {
        return c::bufferPointer();
    }

    TypeSpecifierTranslationResult type::Buffer::translateTypeSpecifier () const {
        // This assumes that the nested type can only be simple, and so will always be translatable.
        return tpl::TypeSpecifier{
            .type     = c::floatingType(),
            .constant = true,
            .constptr = true
        };
    }

    SameTypeResult type::Buffer::sameType (type::Buffer const & other) const {
        return size == other.size;
    }

    SameTypeResult type::Buffer::identicalType (type::Buffer const & other) const {
        return sameType(other);
    }

    DefinitionProcessingResult type::Buffer::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> & definition
    ) const {
        if (!definition)
            return esl::result_error{"Buffers must be explicitly initialized."};

        auto valueType = interface::resolvedValueType(*definition);
        if (!(interface::sameType(*this) || target::category{} <<= valueType))
            return esl::result_error{"Initializing from an incompatible type."};

        return [&] (CompleteValue const & value) -> DefinitionProcessingResult {
            return Variable{value};

        } | [&] (TypedExpression const & value) -> DefinitionProcessingResult {
            auto ptrType = c::bufferPointer();
            auto varName = c::variableName(c::id(ctx.nextId()));
            auto local   = c::definition(ptrType, varName, std::move(value.expression));

            /***
            local:
            cth_float const * const <var> = <definition>;
            ***/
            ctx.insertStatement(local);

            /***
            <var>
            ***/
            return Variable{TypedName{*this, varName}};

        } || target::category{} <<= *definition;
    }

    //// Function ////

    DisplayResult type::Function::display () const {
        using Target = target::nested<target::component_vector, target::category>;
        // TODO: Fix interface::displayTuple to be able to display the output type unparenthesized when single.
        return
            "(" + esl::join(", ", interface::display || Target{} <<= out) + ")" +
            "(" + esl::join(", ", interface::display || Target{} <<= in)  + ")";
    }

    SameTypeResult type::Function::sameType (type::Function const & other) const {
        using Target = target::nested<target::component_vector, target::category>;
        auto outResult = interface::sameTypes || Target{} <<= args(out, other.out);
        auto inResult  = interface::sameTypes || Target{} <<= args(in,  other.in);
        return outResult && inResult && esl::all(*outResult) && esl::all(*inResult);
    }

    SameTypeResult type::Function::identicalType (type::Function const & other) const {
        return sameType(other);
    }

    DefinitionProcessingResult type::Function::processDefinition (
        context::Main & ctx,
        std::optional<ResolvedValue> & definition
    ) const {
        if (!definition)
            return esl::result_error{"Functions must be initialized explicitly."};

        auto valResult = definition->get<CompleteValue>();
        if (!valResult)
            return esl::result_error{"Initializing from an incompatible type."};
        auto funResult = valResult->get<sem::value::Function>();
        if (!funResult)
            return esl::result_error{"Initializing from an incompatible type."};
        auto & fun = *funResult;

        if (!interface::sameTypes(fun.valueType, *this))
            return esl::result_error{"Initializing from an incompatible type."};

        if (!fun.runtimeClosure())
            // No run-time captures:
            return Variable{CompleteValue{fun}};

        // Run-time captures:
        auto varType = c::autoType();
        auto varName = c::closureVariableName(c::id(ctx.nextId()));
        auto local   = c::definition(varType, varName, *fun.closureVariable);

        /***
        __auto_type <closure> = <definition>;
        ***/
        ctx.insertStatement(local);

        return Variable{CompleteValue{sem::value::Function{fun.definition, varName}}};
    }

}

#if 0 // Old code...
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
#endif
