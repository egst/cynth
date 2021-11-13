#pragma once

#include "util/general.hpp"
#include "util/iterator.hpp"

#include <cstddef>
#include <type_traits>
#include <tuple>

namespace cynth::util {

    namespace detail {

        // Note: I can't use raw pointers here, because of the possible std::vector<bool> optimization.
        template <typename C, bool Constant>
        using container_iterator = std::conditional_t <
            Constant,
            decltype(std::declval<C>().cbegin()),
            decltype(std::declval<C>().begin())
            //typename std::remove_reference_t<C>::const_iterator,
            //typename std::remove_reference_t<C>::iterator
        >;

        template <bool Constant, util::range... Cs>
        struct zip_iterator: util::iterator<zip_iterator<Constant, Cs...>> {
            using value_types = std::conditional_t<
                Constant,
                std::tuple<std::add_const_t<util::range_value_type<Cs>>...>,
                std::tuple<util::range_value_type<Cs>...>
            >;
            using iterators = std::tuple<container_iterator<Cs, Constant>...>;

            zip_iterator ()                     = default;
            zip_iterator (zip_iterator const &) = default;
            zip_iterator (zip_iterator &&)      = default;

            zip_iterator (container_iterator<Cs, Constant>... iters): iters{iters...} {}
            zip_iterator (iterators                           iters): iters{iters} {}

            // Note: The reference type could be a "fake reference proxy type
            decltype(auto) dereference () const {
                return std::apply([] (auto &&... iters) { return std::make_tuple(*iters...); }, iters);
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

    namespace detail {

        template <typename T>
        using ref_or_val = std::conditional_t<
            std::is_lvalue_reference_v<T>,
            T,                         // Keep lvalue references.
            std::remove_reference_t<T> // Remove rvalue references (and keep direct values untouched).
        >;

    }

    template <util::range... Cs>
    struct zip {
        using size_type       = std::size_t;
        using difference_type = std::ptrdiff_t;
        using value_type      = std::tuple<util::range_value_type<Cs>...>;
        using reference       = std::tuple<util::range_value_type<Cs> &...>;
        using const_reference = std::tuple<util::range_value_type<Cs> const &...>;
        //using pointer         = value_type *; // Or maybe a tuple of pointers?
        //using const_pointer   = value_type const *;
        using iterator        = detail::zip_iterator<false, Cs...>;
        using const_iterator  = detail::zip_iterator<true,  Cs...>;

        constexpr zip (Cs &&... containers): containers{std::forward<Cs>(containers)...} {}
        //constexpr zip (std::tuple<Cs const &...> containers): containers{containers} {}

        constexpr zip ()                  = default;
        constexpr zip (zip const & other) = default;
        constexpr zip (zip &&      other) = default;

        constexpr zip & operator = (zip const & other) = default;
        constexpr zip & operator = (zip &&      other) = default;

        std::size_t size () const {
            return std::get<0>(containers).size();
        }

        constexpr bool empty () const {
            return std::get<0>(containers).empty();
        }

        const_iterator begin () const {
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

        iterator begin () {
            return std::apply([] (auto &&... containers) { return iterator{containers.begin()...}; }, containers);
        }

        iterator end () {
            return begin() + size();
        }

        constexpr void swap (zip & other) {
            containers.swap(other.containers);
        }

    private:
        std::tuple<detail::ref_or_val<Cs>...> containers;
    };

    template <typename... Cs> zip(Cs &&... containers) -> zip<Cs...>;


}
