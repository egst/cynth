#pragma once

#include "util/debug.hpp"
#include "util/general.hpp"

#include <type_traits>
#include <concepts>
#include <utility>

namespace cynth {

    // Note: Most categories are kept non-copyable mostly just to make sure, that the copy/move semantics distinction works as expected.
    template <typename Derived, typename Variant, bool Copyable = true>
    struct category_base {
        using variant = Variant;
        variant value;

        category_base () = delete;
        //category_base (category_base const &) = delete;

        template <util::variant_member<variant> T> requires (util::temporary<T> || Copyable)
        constexpr category_base (T && other):
            value{std::forward<T>(other)} {
            util::dout << "category{node}\n";
        }

        template <util::variant_member<variant> T> requires (util::temporary<T> || Copyable)
        constexpr Derived & operator = (T && other) {
            util::dout << "category = node\n";
            value = std::forward<T>(other);
            return *static_cast<Derived *>(this);
        }

        template <typename T> requires util::compatible_variant<decltype(T::value), variant> && (util::temporary<T> || Copyable)
        constexpr category_base (T && other):
            value{util::variant_cast<variant>(util::forward_like<T>(other.value))} {
            util::dout << "category{category}\n";
        }

        template <typename T> requires util::compatible_variant<decltype(T::value), variant> && (util::temporary<T> || Copyable)
        constexpr Derived & operator = (T && other) {
            util::dout << "category = category\n";
            std::visit([this] <util::temporary U> (U && other_value) { value = util::forward_like<T>(other_value); }, util::forward_like<T>(other.value));
            return *static_cast<Derived *>(this);
        }
    };

    namespace detail {

        template <typename T>
        concept categorial =
            std::derived_from<T, category_base<T, typename T::variant, true>> ||
            std::derived_from<T, category_base<T, typename T::variant, false>>;

    }

    template <typename T>
    concept categorial = detail::categorial<std::remove_cvref_t<T>>;

}
