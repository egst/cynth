#include "syn/nodes/array_elements.hpp"

//#include <algorithm>
#include <type_traits>
#include <utility>

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/concepts.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"

#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/compound.hpp"
#include "sem/numeric_types.hpp"
#include "sem/values.hpp"

// TMP
#include "esl/debug.hpp"
#include "esl/macros.hpp"

namespace cynth {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::ArrayElementProcessingResult;
    using sem::CompleteValue;
    using sem::TypedExpression;
    using sem::Integral;
    using sem::ResolvedValue;
    using sem::ArrayAllocation;

    DisplayResult syn::node::RangeTo::display () const {
        return
            (interface::display || target::category{} <<= *from) + " to " +
            (interface::display || target::category{} <<= *to);
    }

    ArrayElementProcessingResult syn::node::RangeTo::processArrayElement (context::Main & ctx) const {
        return [] (CompleteValue && from, CompleteValue && to) {
            // Fully comp-time range:
            return [] <typename Value> (Value && from, Value && to) -> ArrayElementProcessingResult requires (
                esl::same_but_cvref<Value, sem::value::Int> || esl::same_but_cvref<Value, sem::value::Float>
            ) {
                using Wrap     = std::remove_cvref_t<Value>;
                using Type     = decltype(Wrap::value);
                auto fromValue = std::move(from).get();
                auto toValue   = std::move(to).get();
                auto step      = static_cast<Type>(1); // Default step - `1` or `1.0`.

                esl::tiny_vector<ResolvedValue> range;
                for (Type i = fromValue; i < toValue; i += step)
                    range.emplace_back(CompleteValue{Wrap{i}});
                return range;

            } | [] <typename Value> (Value && from, Value && to) -> ArrayElementProcessingResult {
                // Note: I guess bools could work, but they don't make much sense.
                return esl::result_error{"Values in a from..to array element must be integers or floats."};

            } | [] (auto && from, auto && to) -> ArrayElementProcessingResult {
                // Note: There will be no implicit conversion to a common type in the first version.
                return esl::result_error{"Incompatible types in a from..to array element."};

            } || target::category{} <<= args(std::move(from), std::move(to));

        } | [&] (auto &&, auto &&) -> ArrayElementProcessingResult {
            // Run-time range:
            // Note: It would be impossible to know their size at compile time.
            return esl::result_error{"From..to array elements with run-time values not supported."};

        } || target::nested<target::result, target::category>{} <<= args(
            esl::single || target::result{} <<= interface::processExpression(ctx) || target::category{} <<= *from,
            esl::single || target::result{} <<= interface::processExpression(ctx) || target::category{} <<= *to
        );
    }

    DisplayResult syn::node::RangeToBy::display () const {
        return
            (interface::display || target::category{} <<= *from) + " to " +
            (interface::display || target::category{} <<= *to)   + " by " +
            (interface::display || target::category{} <<= *by);
    }

    ArrayElementProcessingResult syn::node::RangeToBy::processArrayElement (context::Main & ctx) const {
        return [] (CompleteValue && from, CompleteValue && to, CompleteValue && by) {
            // Fully comp-time range:
            return [] <typename Value> (Value && from, Value && to, Value && by)
            -> ArrayElementProcessingResult requires (
                esl::same_but_cvref<Value, sem::value::Int> || esl::same_but_cvref<Value, sem::value::Float>
            ) {
                using Wrap     = std::remove_cvref_t<Value>;
                using Type     = decltype(Wrap::value);
                auto fromValue = std::move(from).get();
                auto toValue   = std::move(to).get();
                auto step      = std::move(by).get();

                esl::tiny_vector<ResolvedValue> range;
                for (Type i = fromValue; i < toValue; i += step)
                    range.emplace_back(CompleteValue{Wrap{i}});
                return range;

            } | [] <typename Value> (Value &&, Value &&, Value &&) -> ArrayElementProcessingResult {
                // Note: I guess bools could work, but they don't make much sense.
                return esl::result_error{"Values in a from..to..by array element must be integers or floats."};

            } | [] (auto &&, auto &&, auto &&) -> ArrayElementProcessingResult {
                // Note: There will be no implicit conversion to a common type in the first version.
                return esl::result_error{"Incompatible types in a from..to..by array element."};

            } || target::category{} <<= args(std::move(from), std::move(to), std::move(by));

        } | [&] (auto &&, auto &&, auto &&) -> ArrayElementProcessingResult {
            // Run-time range:
            // Note: It would be impossible to know their size at compile time.
            return esl::result_error{"From..to..by array elements with run-time values not supported."};

        } || target::nested<target::result, target::category>{} <<= args(
            esl::single || target::result{} <<= interface::processExpression(ctx) || target::category{} <<= *from,
            esl::single || target::result{} <<= interface::processExpression(ctx) || target::category{} <<= *to,
            esl::single || target::result{} <<= interface::processExpression(ctx) || target::category{} <<= *by
        );
    }

    DisplayResult syn::node::Spread::display () const {
        return "..." + (interface::display || target::category{} <<= *container);
    }

    ArrayElementProcessingResult syn::node::Spread::processArrayElement (context::Main & ctx) const {
        return [] (CompleteValue && container) {
            return [] (sem::value::Array && container) {
                auto arrayType = container.valueType;
                return [&] (ArrayAllocation * alloc) -> ArrayElementProcessingResult {
                    return [] (auto const & value) {
                        return ResolvedValue{value};
                    } || target::view_tiny_result{} <<= alloc->trimmedValue(arrayType.size);

                } | [&] (std::string const & alloc) -> ArrayElementProcessingResult {
                    esl::tiny_vector<ResolvedValue> range;
                    for (std::size_t i = 0; i < arrayType.size; ++i) {
                        auto expr = c::arraySubscript(alloc, c::integralLiteral(i));
                        range.emplace_back(TypedExpression{*arrayType.type, expr});
                    }
                    return range;

                } || target::variant{} <<= container.allocation;

            } | [] (auto &&) -> ArrayElementProcessingResult {
                return esl::result_error{"Only array values can be spread into array elements."};

            } || target::category{} <<= std::move(container);

        } | [&] (TypedExpression && container) {
            // Run-time range:
            return [&] (sem::type::Array && arrayType) -> ArrayElementProcessingResult {
                esl::tiny_vector<ResolvedValue> range;
                for (std::size_t i = 0; i < arrayType.size; ++i) {
                    auto expr = c::arraySubscript(std::move(container).expression, c::integralLiteral(i));
                    range.emplace_back(TypedExpression{*arrayType.type, expr});
                }
                return range;

            } | [] (auto &&) -> ArrayElementProcessingResult {
                return esl::result_error{"Only array values can be spread into array elements."};

            } || target::category{} <<= std::move(container).type;

        } || target::nested<target::result, target::category>{} <<=
            esl::single || target::result{} <<= interface::processExpression(ctx) || target::category{} <<= *container;
    }

}

namespace esl {

    using cynth::syn::node::RangeTo;
    using cynth::syn::node::RangeToBy;
    using cynth::syn::node::Spread;

    template <>
    void component_deleter<RangeTo>::operator () (RangeTo * ptr) const {
        delete ptr;
    }

    template <>
    RangeTo * component_allocator<RangeTo>::operator () (RangeTo const & other) const {
        return new RangeTo{other};
    }

    template <>
    RangeTo * component_allocator<RangeTo>::operator () (RangeTo && other) const {
        return new RangeTo{std::move(other)};
    }

    template <>
    void component_deleter<RangeToBy>::operator () (RangeToBy * ptr) const {
        delete ptr;
    }

    template <>
    RangeToBy * component_allocator<RangeToBy>::operator () (RangeToBy const & other) const {
        return new RangeToBy{other};
    }

    template <>
    RangeToBy * component_allocator<RangeToBy>::operator () (RangeToBy && other) const {
        return new RangeToBy{std::move(other)};
    }

    template <>
    void component_deleter<Spread>::operator () (Spread * ptr) const {
        delete ptr;
    }

    template <>
    Spread * component_allocator<Spread>::operator () (Spread const & other) const {
        return new Spread{other};
    }

    template <>
    Spread * component_allocator<Spread>::operator () (Spread && other) const {
        return new Spread{std::move(other)};
    }

}
