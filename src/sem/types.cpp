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

#include "sem/context.hpp"
#include "sem/interface.hpp"
#include "sem/misc.hpp"
#include "sem/numeric_types.hpp"
#include "sem/translation_context.hpp"

// TMP
#include "esl/debug.hpp"
#include "esl/macros.hpp"

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

namespace cynth::sem {

    namespace {

        StatementTranslationResult translateSimpleDefinition (
            TranslationContext & ctx,
            std::optional<std::string> const & definition,
            std::string const & typeName
        ) {
            /*
            cth_{type} var_{nextId()} = {definition};
            */

            auto def = definition.value_or("0");
            auto id  = std::to_string(ctx.nextId());

            auto result = c::definition(c::typeName(typeName), c::variableName(id), def);

            return ctx.insertStatement(result);
        }

        enum ArrayKind {
            constant,
            nonConst,
            stat // static
        };

        esl::result<void> translateArrayDefinition (
            TranslationContext & ctx,
            type::Array const & type,
            ArrayKind kind,
            std::optional<std::string> const & definition
        ) {
            auto typeNamesResult = esl::unite_results(
                esl::lift<esl::target::component_vector, esl::target::category>(typeName)(type.type)
            );
            if (!typeNamesResult)
                return typeNamesResult.error();

            auto types   = c::templateArguments(*typeNamesResult);
            auto valId   = std::to_string(ctx.nextId());
            auto varId   = std::to_string(ctx.nextId());
            auto size    = std::to_string(type.size);
            auto valType = c::arrayType(size, types);
            auto tupType = c::tupleType(types);
            auto valName = c::valueName(valId);
            auto varName = c::variableName(varId);
            auto init    = definition ? c::statement(c::arrayCopyTo(*definition, varName)) : "";
            // TODO: Explicitly initialize to all zeros? What does C do in static and stack allocations?
            // I think it initilizes to zero in static allocations and keeps it uninitialized on the stack, but I might be mistaken.

            if (kind == ArrayKind::stat) {
                /*
                global:
                cth_arr${size}${type1}${type2}$... const cth_val_{i = nextId()}; // implicitly const
                local:
                cth_tup${type1}${type2}$... const * const var_{j = nextId()} = cth_val_{i}.value; // implicitly const & const-valued
                arr_copy_to({definitino}, var_{j});

                note, that some values in the tuple struct might already be const, but adding redundant const to the whole struct is still ok
                */

                if (!definition)
                    return esl::result_error{"Static arrays must be explicitly initialized."};

                auto ptrType = c::constness(c::pointer(c::constness(tupType)));
                auto alloc   = c::statement(c::declaration(c::constness(valType), c::global(valName)));
                auto local   = c::statement(c::definition(ptrType, varName, c::arrayValue(c::global(valName))));

                return esl::chain_results(
                    [&ctx, &alloc] { return ctx.insertStaticAllocation(alloc); },
                    [&ctx, &local] { return ctx.insertStatement(local); },
                    [&ctx, &init]  { return init.empty() ? esl::result<void>{} : ctx.insertStatement(init); }
                );

            }

            /*
            function scope:
            cth_arr${size}${type1}${type2}$... val_{i = nextId()};
            local:
            cth_tup${type1}${type2}$... * var_{j = nextId()} = val_{i}.value;
            cth_tup${type1}${type2}$... * const var_{j = nextId()} = val_{i}.value; // const
            arr_copy_to({definitino}, var_{j})

            note that const values will be specified in the tuple struct so there is no need for more const specifiers
            */

            auto ptrType = kind == ArrayKind::constant ? c::constness(c::pointer(tupType)) : c::pointer(tupType);
            auto alloc   = c::statement(c::declaration(valType, valName));
            auto local   = c::statement(c::definition(ptrType, varName, c::arrayValue(valName)));

            return esl::chain_results(
                [&ctx, &alloc] { return ctx.insertFunctionAllocation(alloc); },
                [&ctx, &local] { return ctx.insertStatement(local); },
                [&ctx, &init]  { return init.empty() ? esl::result<void>{} : ctx.insertStatement(init); }
            );
        };

    }

    //// Bool ////

    DisplayResult type::Bool::display () const {
        return "Bool";
    }

    CommonTypeResult type::Bool::commonType (type::Bool const &) const {
        return {type::Bool{}};
    }

    CommonTypeResult type::Bool::commonType (type::Int const &) const {
        return {type::Int{}};
    }

    CommonTypeResult type::Bool::commonType (type::Float const &) const {
        return {type::Float{}};
    }

    CommonTypeResult type::Bool::commonType (type::In const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    CommonTypeResult type::Bool::commonType (type::Const const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    CommonTypeResult type::Bool::commonType (type::Static const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    bool type::Bool::sameType (type::Bool const &) const {
        return true;
    }

    StatementTranslationResult type::Bool::translateDefinition (
        TranslationContext & ctx,
        std::optional<std::string> const & definition,
        bool
    ) const {
        return translateSimpleDefinition(ctx, definition, type::Bool::typeName);
    }

    //// Int ////

    DisplayResult type::Int::display () const {
        return "Int";
    }

    CommonTypeResult type::Int::commonType (type::Int const &) const {
        return {type::Int{}};
    }

    CommonTypeResult type::Int::commonType (type::Float const &) const {
        return {type::Float{}};
    }

    CommonTypeResult type::Int::commonType (type::In const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    CommonTypeResult type::Int::commonType (type::Const const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    CommonTypeResult type::Int::commonType (type::Static const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    bool type::Int::sameType (type::Int const &) const {
        return true;
    }

    StatementTranslationResult type::Int::translateDefinition (
        TranslationContext & ctx,
        std::optional<std::string> const & definition,
        bool
    ) const {
        return translateSimpleDefinition(ctx, definition, type::Int::typeName);
    }

    //// Float ////

    DisplayResult type::Float::display () const {
        return "Float";
    }

    CommonTypeResult type::Float::commonType (type::Float const &) const {
        return {type::Float{}};
    }

    CommonTypeResult type::Float::commonType (type::In const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    CommonTypeResult type::Float::commonType (type::Const const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    CommonTypeResult type::Float::commonType (type::Static const & other) const {
        using target = esl::target::nested<esl::target::component, esl::target::category>;
        return esl::lift_nary<esl::target::direct, target>(sem::commonType)(*this, other.type);
    }

    bool type::Float::sameType (type::Float const &) const {
        return true;
    }

    StatementTranslationResult type::Float::translateDefinition (
        TranslationContext & ctx,
        std::optional<std::string> const & definition,
        bool
    ) const {
        return translateSimpleDefinition(ctx, definition, type::Float::typeName);
    }

    //// String ////

    DisplayResult type::String::display () const {
        return "String";
    }

    CommonTypeResult type::String::commonType (type::String const &) const {
        return {type::String{}};
    }

    bool type::String::sameType (type::String const &) const {
        return true;
    }

    StatementTranslationResult type::String::translateDefinition (
        TranslationContext &,
        std::string const &,
        bool
    ) const {
        return esl::result_error{"Strings are not implemented yet."};
    }

    //// In ////

    DisplayResult type::In::display () const {
        return "T in"; // TODO
    }

    TypeDecayResult type::In::decayType () const {
        return *type;
    }

    bool type::In::sameType (type::In const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(sem::sameType)(type, other.type);
    }

    TypeCompletionResult type::IncompleteIn::completeType (Context & ctx) const {
        auto result = esl::lift<esl::target::component, esl::target::category>(sem::completeType(ctx))(type);
        if (!result)
            return result.error();
        return {type::In{{
            .type = *result
        }}};
    }

    StatementTranslationResult type::In::translateDefinition (
        TranslationContext &,
        std::string const &,
        bool
    ) const {
        return esl::result_error{"TODO"};
    }

    //// Out ////

    DisplayResult type::Out::display () const {
        return "T out"; // TODO
    }

    TypeDecayResult type::Out::decayType () const {
        return *type;
    }

    bool type::Out::sameType (type::Out const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(sem::sameType)(type, other.type);
    }

    TypeCompletionResult type::IncompleteOut::completeType (Context & ctx) const {
        auto result = esl::lift<esl::target::component, esl::target::category>(sem::completeType(ctx))(type);
        if (!result)
            return result.error();
        return {type::Out{{
            .type = *result
        }}};
    }

    StatementTranslationResult type::Out::translateDefinition (
        TranslationContext &,
        std::string const &,
        bool
    ) const {
        return esl::result_error{"TODO"};
    }

    //// Const ////

    DisplayResult type::Const::display () const {
        return "T const"; // TODO
    }

    // TODO: Might not be needed.
    /** `T_const` */
    TypeNameResult type::Const::getTypeName () const {
        auto result = esl::lift<esl::target::component, esl::target::category>(sem::typeName)(type);
        if (!result)
            return result.error();
        return *result + "_const";
    }

    TypeDecayResult type::Const::decayType () const {
        return *type;
    }

    CommonTypeResult type::Const::commonType (type::Const const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(sem::commonType)(type, other.type);
        /*
        auto result = esl::lift<esl::target::component, esl::target::category>(sem::commonType)(type, other.type);
        if (!result)
            return result.error();
        return {type::Const{{
            .type = *result
        }}};
        */
    }

    CommonTypeResult type::Const::commonType (type::Static const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(sem::commonType)(type, other.type);
    }

    CommonTypeResult type::Const::commonType (type::Array const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(
            [&other] (type::Array const & a) -> esl::result<CompleteType> {
                return a.commonType(other);
            },
            [] (auto const & a) -> esl::result<CompleteType> {
                return esl::result_error{"Non-array const type does not have a common type with an array type."};
            }
        )(type);
    }

    bool type::Const::sameType (type::Const const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(sem::sameType)(type, other.type);
    }

    TypeCompletionResult type::IncompleteConst::completeType (Context & ctx) const {
        auto result = esl::lift<esl::target::component, esl::target::category>(sem::completeType(ctx))(type);
        if (!result)
            return result.error();
        return {type::Const{{
            .type = *result
        }}};
    }

    StatementTranslationResult type::Const::translateDefinition (
        TranslationContext & ctx,
        std::optional<std::string> const & definition,
        bool compval
    ) const {
        if (compval) return {}; // Skip compconst values.
        return esl::lift<esl::target::component, esl::target::category>(
            [&ctx, &definition] (type::Array const & type) -> esl::result<void> {
                return translateArrayDefinition(ctx, type, ArrayKind::constant, definition);
            },
            [&ctx, &definition] <interface::simpleType T> (T const &) -> esl::result<void> {
                /*
                cth_{type}_const var_{nextId()} = {definition};
                */
                return translateSimpleDefinition(ctx, definition, c::constType(T::typeName));
            },
            [] (auto const &) -> esl::result<void> {
                return esl::result_error{"Only simple types and arrays may be marked const."};
            }
        )(type);
    }

    //// Static ////

    DisplayResult type::Static::display () const {
        return "T static"; // TODO
    }

    TypeDecayResult type::Static::decayType () const {
        return *type;
    }

    CommonTypeResult type::Static::commonType (type::Static const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(sem::commonType)(type, other.type);
    }

    CommonTypeResult type::Static::commonType (type::Array const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(
            [&other] (type::Array const & a) -> esl::result<CompleteType> {
                return a.commonType(other);
            },
            [] (auto const & a) -> esl::result<CompleteType> {
                return esl::result_error{"Non-array static type does not have a common type with an array type."};
            }
        )(type);
    }

    bool type::Static::sameType (type::Static const & other) const {
        return esl::lift<esl::target::component, esl::target::category>(sem::sameType)(type, other.type);
    }

    TypeCompletionResult type::IncompleteStatic::completeType (Context & ctx) const {
        auto result = esl::lift<esl::target::component, esl::target::category>(sem::completeType(ctx))(type);
        if (!result)
            return result.error();
        return {type::Static{{
            .type = *result
        }}};
    }

    namespace {

        StatementTranslationResult translateStaticDefinition (
            TranslationContext & ctx,
            std::optional<std::string> const & definition,
            std::string const & typeName
        ) {
            /*
            global:
            cth_{type} const cth_val_{i = nextId()} = {definition};
            local:
            cth_{type} const * var_{nextId()} = &cth_val_{i};
            */

            if (!definition)
                return esl::result_error{"Static values must be explicitly initialized."};

            auto def     = *definition;
            auto valId   = std::to_string(ctx.nextId());
            auto varId   = std::to_string(ctx.nextId());
            auto valType = c::typeName(typeName);
            auto varType = c::pointer(valType);
            auto valName = c::global(c::valueName(valId));
            auto varName = c::variableName(varId);
            auto target  = c::addressof(valName);
            auto alloc   = c::definition(valType, valName, def);
            auto local   = c::definition(varType, varName, target);

            return esl::chain_results(
                [&ctx, &alloc] { return ctx.insertStaticAllocation(alloc); },
                [&ctx, &local] { return ctx.insertStatement(local); }
            );
        }

    }

    StatementTranslationResult type::Static::translateDefinition (
        TranslationContext & ctx,
        std::optional<std::string> const & definition,
        bool compval
    ) const {
        if (compval) return {}; // Skip compconst values. (Static types are implicitly const.)
        return esl::lift<esl::target::component, esl::target::category>(
            [&ctx, &definition] (type::Array const & type) -> esl::result<void> {
                return translateArrayDefinition(ctx, type, ArrayKind::stat, definition);
            },
            [&ctx, &definition] <interface::simpleType T> (T const &) -> esl::result<void> {


                return esl::result_error{"TODO"};
            },
            [] (auto const &) -> esl::result<void> {
                return esl::result_error{"Only simple types and arrays can be marked static."};
            }
        )(type);
    }

    //// Array ////

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

    CommonTypeResult type::Array::commonType (type::Array const & other) const {
        auto results = (esl::lift<esl::target::component_vector, esl::target::category>(
            [] <typename T, typename U> (T const & a, U const & b) -> std::optional<CompleteType> {
            //requires (std::sameType_as<T, U> || !std::sameType_as<T, type::Const> && std::sameType_as<U, type::Const>)
                if (sem::sameType(a, b))
                    return {a};
                return {};
            },
            [] <typename T> (type::Const const & a, T const & b) -> std::optional<CompleteType>
            requires (!std::same_as<T, type::Const>) {
                if (sem::sameType(a, b))
                    return {a};
                if (sem::sameType(a, type::Const{{.type = {b}}}))
                    return {type::Const{{a}}};
                return {};
            },
            [] <typename T> (T const & a, type::Const const & b) -> std::optional<CompleteType>
            requires (!std::same_as<T, type::Const>) {
                if (sem::sameType(a, b))
                    return {a};
                if (sem::sameType(type::Const{{.type = {a}}}, b))
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

    bool type::Array::sameType (type::Array const & other) const {
        auto result = esl::lift<esl::target::component_vector, esl::target::category>(sem::sameType)(type, other.type);
        return result && size == other.size && esl::all(*result);
    }

    TypeCompletionResult type::IncompleteArray::completeType (Context & ctx) const {
        auto typeResult = esl::unite_results(
            esl::lift<esl::target::component_vector, esl::target::category>(sem::completeType(ctx))(type)
        );
        if (!typeResult)
            return typeResult.error();

        auto sizeResult = esl::lift<esl::target::component, esl::target::category>(
            [] (value::Unknown const &) -> esl::result<int> {
                return esl::result_error{"Unknown array size."};
            },
            [&ctx] <interface::value Value> (Value const & value) -> esl::result<int> {
                return esl::lift<esl::target::result, esl::target::category>(get<sem::Integral>)(
                    sem::convert(ctx)(value, type::Int{})
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

    StatementTranslationResult type::Array::translateDefinition (
        TranslationContext & ctx,
        std::optional<std::string> const & definition,
        bool
    ) const {
        return translateArrayDefinition(ctx, *this, ArrayKind::nonConst, definition);
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

    CommonTypeResult type::Buffer::commonType (type::Buffer const & other) const {
        if (size != other.size)
            return esl::result_error{"No common type for two buffers because of different sizes."};
        return {*this};
    }

    bool type::Buffer::sameType (type::Buffer const & other) const {
        return size == other.size;
    }

    TypeCompletionResult type::IncompleteBuffer::completeType (Context & ctx) const {
        auto sizeResult = esl::lift<esl::target::component, esl::target::category>(
            [] (value::Unknown const &) -> esl::result<sem::Integral> {
                return esl::result_error{"Unknown array size."};
            },
            [&ctx] <interface::value Value> (Value const & value) -> esl::result<sem::Integral> {
                return esl::lift<esl::target::result, esl::target::category>(get<sem::Integral>)(
                    sem::convert(ctx)(value, type::Int{})
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

    StatementTranslationResult type::Buffer::translateDefinition (
        TranslationContext &,
        std::string const &,
        bool
    ) const {
        return esl::result_error{"TODO"};
    }

    //// Function ////

    DisplayResult type::Function::display () const {
        return "Output (Input)"; // TODO
    }

    CommonTypeResult type::Function::commonType (type::Function const & other) const {
        auto outResult = esl::lift<esl::target::component_vector, esl::target::category>(sem::sameType)(out, other.out);
        if (!outResult)
            return outResult.error();
        if (!esl::all(*outResult))
            return esl::result_error{"No common type for two functions because of diferent output types."};
        auto inResult = esl::lift<esl::target::component_vector, esl::target::category>(sem::sameType)(in, other.in);
        if (!inResult)
            return inResult.error();
        if (!esl::all(*inResult))
            return esl::result_error{"No common type for two functions because of diferent input types."};
        return {*this};
    }

    bool type::Function::sameType (type::Function const & other) const {
        auto outResult = esl::lift<esl::target::component_vector, esl::target::category>(sem::sameType)(out, other.out);
        auto inResult = esl::lift<esl::target::component_vector, esl::target::category>(sem::sameType)(in, other.in);
        return
            outResult && esl::all(*outResult) &&
            inResult  && esl::all(*inResult);
    }

    TypeCompletionResult type::IncompleteFunction::completeType (Context & ctx) const {
        auto outResult = esl::unite_results(
            esl::lift<esl::target::component_vector, esl::target::category>(sem::completeType(ctx))(out)
        );
        if (!outResult)
            return outResult.error();
        auto inResult = esl::unite_results(
            esl::lift<esl::target::component_vector, esl::target::category>(sem::completeType(ctx))(in)
        );
        if (!inResult)
            return inResult.error();
        return {type::Function{{
            .out = esl::make_component_vector(*outResult),
            .in  = esl::make_component_vector(*inResult)
        }}};
    }

    StatementTranslationResult type::Function::translateDefinition (
        TranslationContext &,
        std::string const &,
        bool
    ) const {
        return esl::result_error{"TODO"};
    }

}
