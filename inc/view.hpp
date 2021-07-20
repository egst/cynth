#pragma once

#include <cstddef>

namespace cynth {

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

}
