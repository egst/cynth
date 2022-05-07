#pragma once

#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>

#include "esl/iterator.hpp"

namespace esl {

    /** A standard range. */
    template <typename T>
    concept range = requires (T r) {
        *r.begin();
        *r.end();
        //++r.begin();
        // TODO: ++r.begin() is sometimes invalid. (Probably because it's assigning to an rvalue.)
    };

    /** A standard range with the .size() method. */
    template <typename T>
    concept sized_range = esl::range<T> && requires (T r) {
        r.size();
    };

    /** Get value type of any range. */
    template <range T>
    using range_value_type = std::remove_reference_t<decltype(*std::declval<T>().begin())>;

    /** Get iterator type of any range. */
    template <range T>
    using range_iterator_type = std::remove_reference_t<decltype(std::declval<T>().begin())>;

    /** A range containing a specific type. */
    template <typename T, typename U>
    concept range_of = esl::range<T> && std::convertible_to<esl::range_value_type<T>, U>;

    /** A sized range containing a specific type. */
    template <typename T, typename U>
    concept sized_range_of = esl::sized_range<T> && std::convertible_to<esl::range_value_type<T>, U>;

    /** A range containing a type constrained by the given type trait. */
    template <typename T, template <typename> typename Constraint>
    concept constrained_range = esl::range<T> && Constraint<esl::range_value_type<T>>::value;

    /** A sized range containing a type constrained by the given type trait. */
    template <typename T, template <typename> typename Constraint>
    concept constrained_sized_range = esl::sized_range<T> && Constraint<esl::range_value_type<T>>::value;

    // Checking if at least move is allowed, because some ranges could contain non-copyable values,
    // while non-movable values can still be copied from an rvalue.

    /** A range with a .push_back() method. */
    template <typename T>
    concept back_pushable_range = range<T> && requires (T target, esl::range_value_type<T> && val) {
        target.push_back(std::move(val));
    };

    /** A range with an .insert() method. */
    template <typename T>
    concept insertable_range = range<T> && requires (T target, esl::range_iterator_type<T> && it) {
        target.insert(it, std::make_move_iterator(it), std::make_move_iterator(it));
    };

    /** A range with a .back_insert() method - a simplified version of the standard .insert() method. */
    template <typename T>
    concept back_insertable_range = range<T> && requires (T target, esl::range_iterator_type<T> && it) {
        target.insert_back(std::make_move_iterator(it), std::make_move_iterator(it));
    };

    template <typename T>
    concept reservable_range = esl::sized_range<T> && requires (T r, std::size_t size) {
        r.reserve(size);
    };

    /**
     *  Usecase: In generic code, where a dummy value conforming to the range requirements above
     *  needs to be passed somewhere with no overhead.
     */
    template <typename T = int>
    struct nullrange {
        struct iterator: esl::iterator<iterator> {
            T dereference () const { return {}; }
            std::ptrdiff_t distance (iterator const &) const { return 0; }
            void advance (std::ptrdiff_t) {}
        };
        constexpr iterator begin     () const { return {}; }
        constexpr iterator end       () const { return {}; }
        constexpr int      size      () const { return 0; }
        constexpr void     reserve   (std::size_t) const {};
        constexpr void     push_back (T const &)   const {};
    };

}
