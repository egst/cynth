#include "syn/nodes/incomplete/expressions/conversion.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include <type_traits>
#include <utility>

#include "esl/category.hpp"
#include "esl/concepts.hpp"
#include "esl/lift.hpp"
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
#include "sem/operations.hpp"
#include "sem/translation.hpp"
#include "sem/values.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::NameExtractionResult;
    using interface::TypeNameExtractionResult;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::ResolvedValue;
    using sem::TypedExpression;
    using sem::FunctionDefinition;

    DisplayResult node::Conversion::display () const {
        return
            (interface::display || target::category{} <<= *type) + " " +
            esl::parenthesized(interface::display || target::category{} <<= *argument);
    }

    namespace {

        esl::result<std::string> createBuffer (
            context::Main                             & ctx,
            sem::Integral                               size,
            esl::component_vector<CompleteType> const & in,
            esl::component_vector<CompleteType> const & out,
            FunctionDefinition                        & definition,
            std::optional<std::string>          const & closureVar
        ) {
            // Allocate a new buffer:
            auto valName  = c::bufferValueName(c::id(ctx.nextId()));
            auto buffType = ctx.global.instantiateType(tpl::Buffer{size});
            auto alloc    = c::statement(c::definition(buffType, valName, c::zeroInitialization()));
            /***
            // global:
            cth_buff$size <val> = {0};
            ***/
            ctx.global.insertAllocation(alloc);

            // Assign the generator:
            if (out.size() != 1 || !out.front().holds_alternative<sem::type::Float>())
                return esl::result_error{"A buffer generator must return a single float value."};
            if (in.size() > 1)
                return esl::result_error{"A buffer generator must take at most one parameter."};
            bool time = in.size() == 1;
            if (time && !in.front().holds_alternative<sem::type::Int>())
                return esl::result_error{"A buffer generator can only take an integral time parameter."};
            auto id = ctx.defineFunction(definition);
            if (!id) return id.error();

            if (closureVar) {
                /***
                // global:
                struct <closuretype> <closureval>;
                ***/
                auto closureType  = id->closureType;
                auto closureVal   = c::closureVariableName(c::id(ctx.nextId())); // TODO: Distinguish closurevars and closurevals
                auto closureAlloc = c::statement(c::declaration(closureType, closureVal));
                ctx.global.insertAllocation(closureAlloc);

                /***
                <closureval> = <closurevar>;
                ***/
                auto closureCopy = c::statement(c::assignment(*closureVar, closureVal));
                ctx.insertStatement(closureCopy);

                ctx.global.registerGenerator(valName, size, id->name, time, closureVal);

            } else
                ctx.global.registerGenerator(valName, size, id->name, time, c::emptyValue());

            return valName;
        }

        template <typename, typename> struct Cast;

        template <> struct Cast<sem::type::Bool,  sem::type::Int>   { constexpr static auto op = sem::runtime::btoi; };
        template <> struct Cast<sem::type::Int,   sem::type::Bool>  { constexpr static auto op = sem::runtime::itob; };
        template <> struct Cast<sem::type::Int,   sem::type::Float> { constexpr static auto op = sem::runtime::itof; };
        template <> struct Cast<sem::type::Float, sem::type::Int>   { constexpr static auto op = sem::runtime::ftoi; };
        template <> struct Cast<sem::type::Bool,  sem::type::Float> { constexpr static auto op = sem::runtime::btof; };
        template <> struct Cast<sem::type::Float, sem::type::Bool>  { constexpr static auto op = sem::runtime::ftob; };

        template <interface::simpleType FromType, interface::simpleType Type>
        esl::result<ResolvedValue> simpleRuntimeValue (
            FromType        const &,
            Type            const & type,
            TypedExpression const & expression
        ) {
            if constexpr (esl::same_but_cvref<FromType, Type>)
                // Same types:
                return {expression};

            else {
                // Note: Without the else, this doesn't compile (with clang at least),
                // because Cast is not specialized for the same types.
                auto converted = c::expression(Cast<FromType, Type>::op(expression.expression));
                return {TypedExpression{type, converted}};
            }
        }

        esl::result<ResolvedValue> runtimeValue (
            CompleteType    const & type,
            TypedExpression const & expression
        ) {
            return [&] <interface::simpleType FromType, interface::simpleType Type> (
                FromType const & fromType, Type const & type
            ) -> esl::result<ResolvedValue> {
                // Simple -> simple:
                return simpleRuntimeValue(fromType, type, expression);

            } | [&] (sem::type::In fromType, interface::simpleType auto const & type) -> esl::result<ResolvedValue> {
                // In -> simple:
                return [&] (interface::simpleType auto const & fromType) -> esl::result<ResolvedValue> {
                    return simpleRuntimeValue(fromType, type, expression);

                } | [&] <typename T> (T const &) -> esl::result<ResolvedValue> requires (!interface::simpleType<T>) {
                    return esl::result_error{"Compound or referential value type in an input type."}; // Implementation error.

                } || target::category{} <<= *fromType.type;

            } | [&] (sem::type::Array const & fromType, sem::type::Array const & type) -> esl::result<ResolvedValue> {
                // Array -> array:
                if (interface::sameTypes(type, fromType))
                    // Same types:
                    return {expression};

                if (fromType.size < type.size)
                    return esl::result_error{"Arrays can only be converted to smaller sizes."};
                if (!(interface::sameTypes || target::category{} <<= args(*fromType.type, *type.type)))
                    return esl::result_error{"Conversion of array element types is not supported yet."};
                /*
                if (!type.constant && fromType.constant)
                    return esl::result_error{"Array conversion can't remove constness of the reference."};
                */
                if (!type.constval() && fromType.constval())
                    return esl::result_error{"Array conversion can't remove constness of the values."};

                return {TypedExpression{
                    .type       = type,
                    .expression = expression.expression,
                }};

            } | [&] (sem::type::Buffer const & fromType, sem::type::Buffer const & type) -> esl::result<ResolvedValue> {
                // Buffer -> buffer:
                if (interface::sameTypes(type, fromType))
                    // Same types:
                    return {expression};

                if (fromType.size < type.size)
                    return esl::result_error{"Buffers can only be converted to smaller sizes."};

                return {TypedExpression{
                    .type       = type,
                    .expression = expression.expression,
                }};

            } | [&] <typename FromType, typename Type> (
                FromType const & fromType, Type const & type
            ) -> esl::result<ResolvedValue> {
                // Other types:
                if (interface::sameTypes(type, fromType))
                    // Same types:
                    return {expression};

                // Different types:
                return esl::result_error{"Unsupported type conversion."};

            } || target::category{} <<= args(
                expression.type,
                type
            );
       }

        esl::result<ResolvedValue> comptimeValue (
            context::Main       & ctx,
            CompleteType  const & type,
            CompleteValue const & value
        ) {
            return [&] <interface::simpleValue Value, interface::simpleType Type> (
                Value value, Type const &
            ) -> esl::result<ResolvedValue> {
                // Simple -> simple:
                if constexpr (esl::same_but_cvref<decltype(Value::valueType), Type>)
                    // Same types:
                    return {CompleteValue{value}};

                // Different types:
                using Wrap = typename std::remove_cvref_t<Type>::Value;
                using Data = decltype(Wrap::value);
                auto converted = Wrap{static_cast<Data>(value.value)};
                return {CompleteValue{converted}};

            } | [&] (sem::value::In value, interface::simpleType auto const & type) -> esl::result<ResolvedValue> {
                // In -> simple:
                auto fromType = value.valueType;
                return [&] (interface::simpleType auto const & fromType) -> esl::result<ResolvedValue> {
                    return simpleRuntimeValue(fromType, type, TypedExpression{fromType, value.allocation});

                } | [&] <typename T> (T const &) -> esl::result<ResolvedValue> requires (!interface::simpleType<T>) {
                    return esl::result_error{"Compound or referential value type in an input type."}; // Implementation error.

                } || target::category{} <<= *fromType.type;

            } | [&] (sem::value::Array value, sem::type::Array const & type) -> esl::result<ResolvedValue> {
                // Array -> array:
                auto fromType = value.valueType;
                if (interface::sameTypes(type, fromType))
                    // Same types:
                    return {CompleteValue{value}};

                if (fromType.size < type.size)
                    return esl::result_error{"Arrays can only be converted to smaller sizes."};
                if (!(interface::sameTypes || target::category{} <<= args(*fromType.type, *type.type)))
                    return esl::result_error{"Conversion of array element types is not supported yet."};
                /*
                if (!type.constant && fromType.constant)
                    return esl::result_error{"Array conversion can't remove constness of the reference."};
                */
                if (!type.constval() && fromType.constval())
                    return esl::result_error{"Array conversion can't remove constness of the values."};

                return {CompleteValue{sem::value::Array{
                    .allocation = value.allocation,
                    .valueType  = type
                }}};

            } | [&] (sem::value::Buffer value, sem::type::Buffer const & type) -> esl::result<ResolvedValue> {
                // Buffer -> buffer:
                auto fromType = value.valueType;
                if (interface::sameTypes(type, fromType))
                    // Same types:
                    return {CompleteValue{value}};

                if (fromType.size < type.size)
                    return esl::result_error{"Buffers can only be converted to smaller sizes."};

                return {CompleteValue{sem::value::Buffer{
                    .allocation = value.allocation,
                    .valueType  = type
                }}};

            } | [&] (sem::value::Function value, sem::type::Buffer const & type) -> esl::result<ResolvedValue> {
                // Function -> buffer:
                auto fromType = value.valueType;
                return [&] (auto alloc) -> esl::result<ResolvedValue> {
                    return {CompleteValue{sem::value::Buffer{
                        .allocation = alloc,
                        .valueType  = type
                    }}};
                } || target::result{} <<= createBuffer(ctx, type.size, fromType.in, fromType.out, value.definition, value.closureVariable);

            } | [&] (auto value, auto const & type) -> esl::result<ResolvedValue> {
                // Other types:
                auto fromType = interface::valueType(value);
                if (interface::sameType(type) || target::category{} <<= fromType)
                    // Same types:
                    return {CompleteValue{value}};

                // Different types:
                return esl::result_error{"Unsupported type conversion."};

            } || target::category{} <<= args(
                value,
                type
            );
        }

    }

    ExpressionProcessingResult node::Conversion::processExpression (context::Main & ctx) const {
        return [&] (auto types, auto values) -> ExpressionProcessingResult {
            return esl::unite_results || target::result{} <<= [&] (auto type, auto value) {
                return [&, &type = type] (CompleteValue const & value) {
                    // Comp-time value:
                    return comptimeValue(ctx, type, value);

                } | [&] (TypedExpression const & expr) {
                    // Run-time value:
                    return runtimeValue(type, expr);

                } || target::category{} <<= value;

            } || target::tiny_vector{} <<= args(types, values);

        } || target::result{} <<= args(
            interface::resolveType(ctx)       || target::category{} <<= *type,
            interface::processExpression(ctx) || target::category{} <<= *argument
        );
    }

    NameExtractionResult node::Conversion::extractNames (context::Lookup & ctx) const {
        return interface::extractNames(ctx) || target::category{} <<= *argument;
    }

    NameExtractionResult node::Conversion::extractTypeNames (context::Lookup & ctx) const {
        return interface::extractTypeNames(ctx) || target::category{} <<= *argument;
    }

}
