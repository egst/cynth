#pragma once

namespace cynth {

    /*
    namespace detail {
        struct exec_functor {
            std::string operator () (node::Auto const &) const {
                return "$";
            }

            template <typename t> requires requires (t a) { a.content; } // TODO: Check if it's a variant.
            std::string operator () (t const & c) const {
                return std::visit(*this, c.content);
            }
        };
    }

    constexpr detail::exec_functor execute;
    */

}
