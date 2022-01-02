#pragma once

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

#include "esl/iterator.hpp"
#include "esl/ranges.hpp"
#include "esl/type_manip.hpp"

namespace esl {

    namespace detail::zip {

        struct counter_iterator: esl::iterator<counter_iterator> {
            counter_iterator ()                         = default;
            counter_iterator (counter_iterator const &) = default;
            counter_iterator (counter_iterator &&)      = default;

            counter_iterator (std::size_t count): count{count} {}

            decltype(auto) dereference () const {
                return count;
            }

            std::ptrdiff_t distance (counter_iterator const & other) const {
                return other.count - count;
            }

            void advance (std::ptrdiff_t offset) {
                count += offset;
            }

        private:
            std::size_t count;
        };

        template <typename C, bool Constant>
        using container_iterator = std::conditional_t <
            Constant,
            decltype(std::declval<C>().cbegin()),
            decltype(std::declval<C>().begin())
        >;

        template <bool Constant, bool Enum, esl::range... Cs>
        struct zip_iterator: esl::iterator<zip_iterator<Constant, Enum, Cs...>> {
            using real_iterators = std::tuple<container_iterator<Cs, Constant>...>;
            using iterators = std::conditional_t<
                Enum,
                esl::concat<std::tuple<counter_iterator>, real_iterators>,
                real_iterators
            >;

            zip_iterator ()                     = default;
            zip_iterator (zip_iterator const &) = default;
            zip_iterator (zip_iterator &&)      = default;

            zip_iterator (std::size_t count, container_iterator<Cs, Constant>... iters) requires (Enum):
                iters{count, iters...} {}
            zip_iterator (container_iterator<Cs, Constant>... iters) requires (!Enum):
                iters{iters...} {}
            zip_iterator (std::size_t count, real_iterators iters) requires (Enum):
                iters{std::tuple_cat(count, iters)} {}
            zip_iterator (real_iterators iters) requires (!Enum):
                iters{iters} {}
            zip_iterator (iterators iters) requires (Enum):
                iters{iters} {}

            decltype(auto) dereference () const {
                return std::apply([] (auto &&... iters) { return std::forward_as_tuple(*iters...); }, iters);
            }

            std::ptrdiff_t distance (zip_iterator const & other) const {
                return std::get<0>(other.iters) - std::get<0>(iters);
            }

            void advance (std::ptrdiff_t offset) {
                std::apply([&offset] (auto &&... iters) { return ((iters + offset), ...); }, iters);
            }

        private:
            iterators iters;
        };

    }

    template <bool Enum, esl::range... Cs>
    struct zip_type {
        using size_type       = std::size_t;
        using difference_type = std::ptrdiff_t;
        using value_type      = std::tuple<esl::range_value_type<Cs>...>;
        using reference       = std::tuple<esl::range_value_type<Cs> &...>;
        using const_reference = std::tuple<esl::range_value_type<Cs> const &...>;
        //using pointer         = value_type *; // Or maybe a tuple of pointers?
        //using const_pointer   = value_type const *;
        using iterator        = detail::zip::zip_iterator<false, Enum, Cs...>;
        using const_iterator  = detail::zip::zip_iterator<true,  Enum, Cs...>;

        template <std::same_as<Cs>... Ts>
        constexpr zip_type (Ts &&... containers): containers{std::forward<Ts>(containers)...} {}

        constexpr zip_type ()                  = default;
        constexpr zip_type (zip_type const & other) = default;
        constexpr zip_type (zip_type &&      other) = default;

        constexpr zip_type & operator = (zip_type const & other) = default;
        constexpr zip_type & operator = (zip_type &&      other) = default;

        std::size_t size () const {
            return std::get<0>(containers).size();
        }

        constexpr bool empty () const {
            return std::get<0>(containers).empty();
        }

        const_iterator begin () const requires (Enum) {
            return std::apply([] (auto &&... containers) { return iterator{0, containers.cbegin()...}; }, containers);
        }

        const_iterator begin () const requires (!Enum) {
            return std::apply([] (auto &&... containers) { return iterator{containers.cbegin()...}; }, containers);
        }

        const_iterator end () const {
            return begin() + size();
        }

        const_iterator cbegin () const {
            return begin();
        }

        const_iterator cend () const {
            return end();
        }

        iterator begin () requires (Enum) {
            return std::apply([] (auto &&... containers) { return iterator{0, containers.begin()...}; }, containers);
        }

        iterator begin () requires (!Enum) {
            return std::apply([] (auto &&... containers) { return iterator{containers.begin()...}; }, containers);
        }

        iterator end () {
            return begin() + size();
        }

        constexpr void swap (zip_type & other) {
            containers.swap(other.containers);
        }

    private:
        std::tuple<esl::lref_or_val<Cs>...> containers;
    };

    template <esl::range... Cs> zip_type(Cs &&...) -> zip_type<false, Cs...>;

    template <esl::range... Cs>
    constexpr zip_type<false, Cs...> zip (Cs &&... containers) {
        return {std::forward<Cs>(containers)...};
    }

    template <esl::range... Cs>
    constexpr zip_type<true, Cs...> enumerate (Cs &&... containers) {
        return {std::forward<Cs>(containers)...};
    }

}
