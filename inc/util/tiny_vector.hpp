#pragma once

#include "util/general.hpp"
#include "util/iterator.hpp"

#include <cstddef>
#include <array>
#include <vector>
#include <initializer_list>
#include <concepts>
#include <utility>
#include <algorithm>
#include <type_traits>
#include <iterator>

namespace cynth::util {

    // Missing features:
    // * reverse iteration (rbegin, rend, reverse_iterator, etc.)
    // * at (operator [] with bounds checking)
    // * insert
    // * erase

    namespace detail {

        template <typename T> using fixed_type   = std::optional <T>;
        template <typename T> using dynamic_type = std::vector   <T>;

        // Note: I can't use raw pointers here, because of the possible std::vector<bool> optimization.
        template <typename T, bool Constant>
        using container_iterator = std::conditional_t <
            Constant,
            typename dynamic_type<T>::const_iterator,
            typename dynamic_type<T>::iterator
        >;

        template <bool Constant, typename T>
        struct tiny_iterator: util::iterator<tiny_iterator<Constant, T>> {
            using value_type = std::conditional_t<Constant, std::add_const_t<T>, T>;
            using fixed_type = std::conditional_t<Constant, std::add_const_t<std::optional<T>>, std::optional<T>>;
            using iterator   = container_iterator<T, Constant>;
            // TODO: I thing it shouldn't actually matter whether it is const or not,
            // because non-const iterator should be a sentinel of a const iterator.

            tiny_iterator ()                      = default;
            tiny_iterator (tiny_iterator const &) = default;
            tiny_iterator (tiny_iterator &&)      = default;

            tiny_iterator (fixed_type & first, iterator rest, std::size_t pos):
                first {&first},
                rest  {rest},
                pos   {pos} {}

            // Note: The reference type could be a "fake reference proxy type
            decltype(auto) dereference () const {
                return pos
                    ? rest[pos - 1]
                    : **first;
            }

            std::ptrdiff_t distance (tiny_iterator const & other) const {
                return other.pos - pos;
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
        using pointer         = value_type &;
        using const_pointer   = value_type const &;
        using iterator        = detail::tiny_iterator<false, value_type>;
        using const_iterator  = detail::tiny_iterator<true,  value_type>;

        using fixed_type   = detail::fixed_type   <T>;
        using dynamic_type = detail::dynamic_type <T>;

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
        }

        bool tiny () const {
            return rest.empty();
        }

        std::size_t size () const {
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
            //return util::as_nonconst(std::as_const(*this).begin());
            return make_iterator(0);
        }

        iterator end () {
            //return util::as_nonconst(std::as_const(*this).end());
            return make_iterator(size());
        }

        constexpr const_reference front () const {
            return *first;
        }

        constexpr const_reference back () const {
            return tiny() ? *first : rest.back();
        }

        constexpr reference front () {
            return util::as_nonconst(std::as_const(*this).front());
        }

        constexpr reference back () {
            return util::as_nonconst(std::as_const(*this).back());
        }

        constexpr const_reference operator [] (size_type offset) const {
            return offset ? rest[offset] : *first;
        }

        constexpr reference operator [] (size_type offset) {
            return util::as_nonconst(std::as_const(*this).operator[](offset));
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
                ? rest.emplace_back(args...)
                : first = value_type{std::forward<Args>(args)...};
        }

        constexpr void push_back (value_type const & value) {
            _push_back<value_type const &>(value);
        }
        constexpr void push_back (value_type && value) {
            _push_back<value_type &&>(std::move(value));
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

    private:
        template <typename U>
        constexpr void _push_back (U && value) {
            if (first)
                rest.push_back(std::forward<U>(value));
            else
                first.emplace(std::forward<U>(value));
                //first = std::forward<U>(value);
                //first = std::make_optional<U>(std::forward<U>(value));
        }

        const_iterator make_iterator (std::size_t position) const {
            return {first, rest.begin(), position};
        }

        iterator make_iterator (std::size_t position) {
            //return util::as_nonconst(std::as_const(*this).make_iterator(position));
            return {first, rest.begin(), position};
        }

        fixed_type   first;
        dynamic_type rest;
    };

}
