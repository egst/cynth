#pragma once

#include "esl/debug.hpp"
#include "esl/concepts.hpp"
#include "esl/type_manip.hpp"
#include "esl/variant.hpp"
#include "esl/lift.hpp"

#include <type_traits>
#include <concepts>
#include <utility>
#include <variant>

namespace esl {

    // Note: Most categories are kept non-copyable mostly just to make sure, that the copy/move semantics distinction works as expected.
    template <typename Derived, typename Variant, bool COPYABLE = true>
    struct category {
        using variant = Variant;
        variant value;

        category () = delete;
        //category (category const &) = delete;

        template <esl::variant_member<variant> T> requires (esl::temporary<T> || COPYABLE)
        constexpr category (T && other):
            value{std::forward<T>(other)} {
            esl::dout << "category{node}\n";
        }

        template <esl::variant_member<variant> T> requires (esl::temporary<T> || COPYABLE)
        constexpr Derived & operator = (T && other) {
            esl::dout << "category = node\n";
            value = std::forward<T>(other);
            return *static_cast<Derived *>(this);
        }

        template <typename T> requires esl::compatible_variant<decltype(T::value), variant> && (esl::temporary<T> || COPYABLE)
        constexpr category (T && other):
            value{esl::variant_cast<variant>(esl::forward_like<T>(other.value))} {
            esl::dout << "category{category}\n";
        }

        template <typename T> requires esl::compatible_variant<decltype(T::value), variant> && (esl::temporary<T> || COPYABLE)
        constexpr Derived & operator = (T && other) {
            esl::dout << "category = category\n";
            std::visit([this] <esl::temporary U> (U && other_value) { value = esl::forward_like<T>(other_value); }, esl::forward_like<T>(other.value));
            return *static_cast<Derived *>(this);
        }
    };

    namespace detail::category {

        template <typename T>
        concept categorial_impl =
            std::derived_from<T, esl::category<T, typename T::variant, true>> ||
            std::derived_from<T, esl::category<T, typename T::variant, false>>;

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

        template <typename...> struct category {};

    }

    template <> struct lift_specialization_map<target::category>:
        lift_implementation<esl::detail::category::lift_impl> {};

}
