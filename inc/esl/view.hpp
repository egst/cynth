#pragma once

#include "esl/concepts.hpp"
#include "esl/lift.hpp"

#include <cstddef>
#include <vector>

namespace esl {

    template <typename It>
    struct view {
        constexpr view (It begin, It end):
            begin_it{begin},
            end_it{end} {}

        constexpr view (It begin, std::size_t count):
            begin_it{begin},
            end_it{begin + count} {}

        std::size_t size () const {
            return end_it - begin_it;
        }

        // TODO: Does this make sense with all those const/non-const versions?

        decltype(auto) begin () {
            return begin_it;
        }

        decltype(auto) begin () const {
            return begin_it;
        }

        decltype(auto) cbegin () const {
            return begin_it;
        }

        decltype(auto) end () {
            return end_it;
        }

        decltype(auto) end () const {
            return end_it;
        }

        decltype(auto) cend () const {
            return end_it;
        }

    private:
        It begin_it;
        It end_it;
    };

    namespace detail::view {

        template <typename Derived, typename F>
        struct lift_impl {
            template <typename T>
            using vector_type = std::vector<T>;

            template <esl::same_template<esl::view> T>
            constexpr auto operator () (T && target) const {
                return esl::lift_on_range<vector_type>(derived(), std::forward<T>(target));
            }

            template <esl::same_template<esl::view> T, esl::same_template<esl::view> U>
            constexpr auto operator () (T && first, U && second) const {
                return esl::lift_on_range<vector_type>(derived(), std::forward<T>(first), std::forward<U>(second));
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

    }

    namespace target {

        struct view { constexpr static lift_target_tag tag = {}; };

    }

    template <> struct lift_specialization_map<target::view>:
        lift_implementation<detail::view::lift_impl> {};

}
