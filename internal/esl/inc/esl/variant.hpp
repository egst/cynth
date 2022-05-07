#pragma once

#include <concepts>
#include <memory>
#include <type_traits>
#include <utility>
#include <variant>

#include "esl/concepts.hpp"
#include "esl/type_manip.hpp"

namespace esl {

    template <typename T, typename V>
    constexpr esl::match_constness<V, T> * getNullable (V & v) {
        return std::holds_alternative<T>(v)
            ? std::addressof(std::get<T>(v))
            : nullptr;
    }

    /** Category containable in the variant.
        e.g. compatible_category<target_variant, source_category>
        or   compatible_category<target_variant> source_category */
    /*template <typename Category, typename Variant>
    concept compatible_category = category::interface<Category> && compatible_variant<decltype(Category::node), Variant>;*/

    template <typename To, compatible_variant<To> From>
    constexpr To variant_cast (From && source) {
        return std::visit([] <typename T> (T && val) -> To { return {esl::forward_like<From>(val)}; }, std::forward<From>(source));
    }

}
