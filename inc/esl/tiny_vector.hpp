#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

#include "esl/concepts.hpp"
#include "esl/iterator.hpp"
#include "esl/lift.hpp"
#include "esl/ranges.hpp"
#include "esl/type_manip.hpp"

// TMP
#include "debug.hpp"

namespace esl {

    // Missing features:
    // * reverse iteration (rbegin, rend, reverse_iterator, etc.)
    // * at (operator [] with bounds checking)
    // * insert
    // * erase

    namespace detail::tiny_vector {

        template <typename T> using fixed_type   = std::optional <T>;
        template <typename T> using dynamic_type = std::vector   <T>;

        // Note: I can't use raw pointers here, because of the possible std::vector<bool> optimization.
        template <typename T, bool constant>
        using TinyContainerIterator = std::conditional_t <
            constant,
            typename dynamic_type<T>::const_iterator,
            typename dynamic_type<T>::iterator
        >;

        template <bool constant, typename T>
        struct tiny_iterator: esl::iterator<tiny_iterator<constant, T>> {
            using value_type    = std::conditional_t<constant, std::add_const_t<T>, T>;
            using fixed_type    = std::conditional_t<constant, std::add_const_t<std::optional<T>>, std::optional<T>>;
            using iterator = TinyContainerIterator<T, constant>;
            // TODO: I thing it shouldn't actually matter whether it is const or not,
            // because non-const iterator should be a sentinel of a const iterator.

            tiny_iterator ()                      = default;
            tiny_iterator (tiny_iterator const &) = default;
            tiny_iterator (tiny_iterator &&)      = default;

            tiny_iterator (fixed_type & first, iterator rest, std::size_t pos):
                first {&first},
                rest  {rest},
                pos   {pos} {}

            decltype(auto) dereference () const {
                return pos
                    ? rest[pos - 1]
                    : **first;
            }

            std::ptrdiff_t distance (tiny_iterator const & other) const {
                return pos - other.pos;
            }

            void advance (std::ptrdiff_t offset) {
                pos += offset;
            }

        private:
            fixed_type * const first;
            iterator           rest;
            std::size_t        pos;
        };

    }

    template <typename T>
    struct tiny_vector {
        using size_type       = std::size_t;
        using difference_type = std::ptrdiff_t;
        using value_type      = T;
        using reference       = value_type &;
        using const_reference = value_type const &;
        using pointer         = value_type *;
        using const_pointer   = value_type const *;
        using iterator        = detail::tiny_vector::tiny_iterator<false, value_type>;
        using const_iterator  = detail::tiny_vector::tiny_iterator<true,  value_type>;

        using fixed_type   = detail::tiny_vector::fixed_type   <T>;
        using dynamic_type = detail::tiny_vector::dynamic_type <T>;

        constexpr tiny_vector ()                          = default;
        constexpr tiny_vector (tiny_vector const & other) = default;
        constexpr tiny_vector (tiny_vector && other)      = default;

        constexpr tiny_vector (std::initializer_list<value_type> init) {
            assign(init.begin(), init.end());
        }

        template <typename It>
        constexpr tiny_vector (It first, It last) {
            assign(first, last);
        }

        constexpr tiny_vector (size_type count, value_type const & value) {
            resize(count, value);
        }

        constexpr explicit tiny_vector (size_type count) {
            resize(count);
        }

        constexpr tiny_vector & operator = (tiny_vector const & other) = default;
        constexpr tiny_vector & operator = (tiny_vector && other)      = default;

        constexpr tiny_vector & operator = (std::initializer_list<value_type> init) {
            assign(init);
            return *this;
        }

        bool tiny () const {
            return rest.empty();
        }

        size_type size () const {
            //return first ? rest.size() : 0;
            return first.has_value() + rest.size();
        }

        constexpr bool empty () const {
            return !first;
        }

        constexpr size_type max_size () const {
            return 1 + rest.max_size();
        }

        constexpr size_type capacity () const {
            return 1 + rest.capacity();
        }

        const_iterator begin () const {
            return make_iterator(0);
        }

        const_iterator end () const {
            return make_iterator(size());
        }

        const_iterator cbegin () const {
            return begin();
        }

        const_iterator cend () const {
            return end();
        }

        iterator begin () {
            //return esl::as_nonconst(std::as_const(*this).begin());
            return make_iterator(0);
        }

        iterator end () {
            //return esl::as_nonconst(std::as_const(*this).end());
            return make_iterator(size());
        }

        constexpr const_reference front () const {
            return *first;
        }

        constexpr const_reference back () const {
            return tiny() ? *first : rest.back();
        }

        constexpr reference front () {
            return esl::as_nonconst(std::as_const(*this).front());
        }

        constexpr reference back () {
            return esl::as_nonconst(std::as_const(*this).back());
        }

        constexpr const_reference operator [] (size_type offset) const {
            return offset ? rest[offset] : *first;
        }

        constexpr reference operator [] (size_type offset) {
            return esl::as_nonconst(std::as_const(*this).operator[](offset));
        }

        constexpr void resize (size_type size) {
            if (!size)
                first = std::nullopt;
            else if (!first)
                first = value_type{};
            rest.resize(std::max<std::size_t>(size - 1, 0));
        }

        constexpr void resize (size_type size, value_type const & value) {
            if (!size)
                first = std::nullopt;
            else if (!first)
                first = value;
            rest.resize(std::max<std::size_t>(size - 1, 0), value);
        }

        constexpr void assign (std::initializer_list<value_type> init) {
            assign(init.begin(), init.end());
        }

        constexpr void assign (size_type size, value_type const & value) {
            if (size)
                first = value;
            else
                first = std::nullopt;
            rest.assign(std::max<std::size_t>(size - 1, 0), value);
        }

        template <typename It>
        constexpr void assign (It first_it, It last_it) {
            std::size_t size = last_it - first_it;
            if (size)
                first = *first_it;
            else
                first = std::nullopt;
            if (size)
                std::copy(first_it + 1, last_it, rest.begin());
        }

        constexpr void shrink_to_fit () {
            rest.shrink_to_fit();
        }

        constexpr void reserve (size_type capacity) {
            rest.reserve(capacity > 1 ? capacity - 1 : 0);
        }

        constexpr void clear () {
            rest.clear();
            first = std::nullopt;
        }

        template <typename... Args>
        constexpr reference emplace_back (Args &&... args) {
            return first
                ? rest.emplace_back(std::forward<Args>(args)...)
                : first.emplace(std::forward<Args>(args)...);
        }

        constexpr void push_back (value_type const & value) {
            push_back_helper<value_type const &>(value);
        }
        constexpr void push_back (value_type && value) {
            push_back_helper<value_type &&>(std::move(value));
        }

        constexpr void pop_back () {
            if (!rest.empty())
                rest.pop_back();
            else
                first = std::nullopt;
        }

        constexpr void swap (tiny_vector & other) {
            first.swap(other.first);
            rest.swap(other.rest);
        }

        /** "insert back" aka append aka `insert(end(), ...)` */
        template <typename It>
        constexpr iterator insert_back (It from, It to) {
            std::ptrdiff_t pos = size();
            if (first)
                rest.insert(rest.end(), from, to);
            else if (from != to) {
                first.emplace(*from);
                rest.insert(rest.end(), from + 1, to);
            }
            return make_iterator(pos);
        }

    private:
        template <typename U>
        constexpr void push_back_helper (U && value) {
            if (first)
                rest.push_back(std::forward<U>(value));
            else
                first.emplace(std::forward<U>(value));
                //first = std::forward<U>(value);
                //first = std::make_optional<U>(std::forward<U>(value));
        }

        const_iterator make_iterator (size_type position) const {
            return {first, rest.begin(), position};
        }

        iterator make_iterator (size_type position) {
            //return esl::as_nonconst(std::as_const(*this).make_iterator(position));
            return {first, rest.begin(), position};
        }

        fixed_type   first;
        dynamic_type rest;
    };

    namespace detail::tiny_vector {

        template <typename Derived, typename F>
        struct lift_impl {
            template <esl::same_template<esl::tiny_vector> T>
            constexpr auto operator () (T && target) const {
                return esl::lift_on_range<esl::tiny_vector>(derived(), std::forward<T>(target));
            }

            template <esl::same_template<esl::tiny_vector> T, esl::same_template<esl::tiny_vector> U>
            constexpr auto operator () (T && first, U && second) const {
                return esl::lift_on_range<esl::tiny_vector>(derived(), std::forward<T>(first), std::forward<U>(second));
            }

        private:

            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct nested_lift_impl {
            template <esl::sized_range T>
            constexpr auto operator () (T && target) const {
                return esl::lift_on_range_cat<esl::tiny_vector>(derived(), std::forward<T>(target));
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct range_lift_impl {
            template <esl::sized_range T>
            constexpr auto operator () (T && target) const {
                return esl::lift_on_range<esl::tiny_vector>(derived(), std::forward<T>(target));
            }

            template <esl::sized_range T, esl::sized_range U>
            constexpr auto operator () (T && first, U && second) const {
                return esl::lift_on_range<esl::tiny_vector>(derived(), std::forward<T>(first), std::forward<U>(second));
            }

        private:

            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

    }

    namespace target {

        struct tiny_vector             { constexpr static lift_target_tag tag = {}; };
        struct nested_tiny_vector_cat  { constexpr static lift_target_tag tag = {}; };
        struct sized_range_tiny_result { constexpr static lift_target_tag tag = {}; };

    }

    template <> struct lift_tpl_target_map<esl::tiny_vector>:
        lift_target<target::tiny_vector> {};

    template <> struct lift_specialization_map<target::tiny_vector>:
        lift_implementation<detail::tiny_vector::lift_impl> {};
    template <> struct lift_specialization_map<target::nested_tiny_vector_cat>:
        lift_implementation<detail::tiny_vector::nested_lift_impl> {};
    template <> struct lift_specialization_map<target::sized_range_tiny_result>:
        lift_implementation<detail::tiny_vector::range_lift_impl> {};

}
