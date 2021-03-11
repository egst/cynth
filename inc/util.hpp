#pragma once

#include <string>
#include <variant>

namespace cynth::util {

    /** Just in case I decide to use some non-std variant implementation. */
    template <typename... T>
    using variant = std::variant<T...>;

    /** Add parentheses around unparenthesized string. */
    inline std::string parenthesized (std::string const & str) {
        return str[0] == '('
            ? str
            : "(" + str + ")";
    }

    /** Overload set from lambda functions. */
    template <typename... fs> struct overload: fs... { using fs::operator()...; };
    template <typename... fs> overload(fs...) -> overload<fs...>;

    namespace detail {
        template <typename, typename...> struct concat;
        template <template <typename...> typename t, typename... ts, typename... us, typename... vs>
        struct concat<t<ts...>, t<us...>, vs...> {
            using type = typename concat<t<ts..., us...>, vs...>::type;
        };
        template <template <typename...> typename t, typename... ts, typename... us>
        struct concat<t<ts...>, t<us...>> {
            using type = t<ts..., us...>;
        };
        template <typename, typename...> struct extend;
        template <template <typename...> typename t, typename... ts, typename... us>
        struct extend<t<ts...>, us...> {
            using type = t<ts..., us...>;
        };
    }

    /** Concatenate template parameters of any variadic type template. */
    template <typename t, typename... us> using concat = typename detail::concat<t, us...>::type;
    /** Add more template parameters to any variadic type template. */
    template <typename t, typename... us> using extend = typename detail::extend<t, us...>::type;

}
