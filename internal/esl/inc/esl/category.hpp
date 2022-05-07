#pragma once

#include <concepts>
#include <type_traits>
#include <utility>
#include <variant>

#include "esl/concepts.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/type_manip.hpp"
#include "esl/variant.hpp"

namespace esl {

    namespace detail::category {

        template <typename Alt, typename Result, typename Cat>
        Result get (Cat && cat) {
            if (!std::holds_alternative<Alt>(cat.value))
                return esl::result_error{"Invalid category alternative requested."};
            return std::get<Alt>(std::forward<Cat>(cat).value);
        }

    }

    // Note: Most categories are kept non-copyable mostly just to make sure, that the copy/move semantics distinction works as expected.
    template <typename Derived, typename Variant>
    struct category {
        using variant = Variant;
        variant value;

        category () = delete;
        //category (category const &) = delete;

        template <esl::variant_member<variant> T>
        constexpr category (T && other):
            value{std::forward<T>(other)} {
        }

        template <esl::variant_member<variant> T>
        constexpr Derived & operator = (T && other) {
            value = std::forward<T>(other);
            return *static_cast<Derived *>(this);
        }

        template <typename T> requires esl::compatible_variant<decltype(T::value), variant>
        constexpr category (T && other):
            value{esl::variant_cast<variant>(esl::forward_like<T>(other.value))} {
        }

        template <typename T> requires esl::compatible_variant<decltype(T::value), variant>
        constexpr Derived & operator = (T && other) {
            std::visit([this] <esl::temporary U> (U && otherValue) {
                value = esl::forward_like<T>(otherValue);
            }, esl::forward_like<T>(other.value));
            return *static_cast<Derived *>(this);
        }

        template <typename U>
        auto get () const & {
            return detail::category::get<U, esl::reference_result<std::add_const_t<U>>>(*this);
        }

        template <typename U>
        auto get () & {
            return detail::category::get<U, esl::reference_result<U>>(*this);
        }

        template <typename U>
        auto get () && {
            return detail::category::get<U, esl::result<U>>(*this);
        }

        template <typename U>
        bool holds_alternative () const {
            return std::holds_alternative<U>(value);
        }

    private:
    };

    namespace detail::category {

        template <typename T>
        concept categorial_impl = std::derived_from<T, esl::category<T, typename T::variant>>;

    }

    template <typename T>
    concept categorial = detail::category::categorial_impl<std::remove_cvref_t<T>>;

    namespace detail::category {

        template <typename Derived, typename F>
        struct lift_impl {
            /** Operate on any number of categories. */
            template <categorial... Ts>
            constexpr decltype(auto) operator () (Ts &&... target) const {
                return std::visit (
                    //derived().template function<>(), // Note: This ends a possible recursion.
                    [this] <typename... Us> (Us &&... value) { return derived().invoke(std::forward<Us>(value)...); },
                    esl::forward_like<Ts>(target.value)...
                );
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

    }

    namespace target {

        struct category { constexpr static lift_target_tag tag = {}; };

    }

    template <> struct lift_specialization_map<target::category>:
        lift_implementation<esl::detail::category::lift_impl> {};

}
