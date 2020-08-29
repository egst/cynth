#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <variant>
#include <utility>
#include <type_traits>
#include <iterator>
#include <algorithm>
#include <concepts>
#include <cmath>

// TODO: Organize
namespace cynth::util {

    namespace detail {
        template <typename t>
        constexpr t powers_of_10 [3 * 3] = {
            1, 10, 100,
            1'000, 10'000, 100'000,
            1'000'000, 10'000'000, 100'000'000/*,
            1'000'000'000, 10'000'000'000, 100'000'000'000,
            1'000'000'000'000, 10'000'000'000'000, 100'000'000'000'000,
            1'000'000'000'000'000, 10'000'000'000'000'000, 100'000'000'000'000'000*/
        };
    }

    template <typename t>
    constexpr t pow10 (std::size_t const p) noexcept { return detail::powers_of_10<t>[p]; }

    inline std::string trim (std::string const & x) { // TODO: Multiple definitions here for reason. (Hence inline)
        return x.substr(1, x.size() - 2);
    }

    inline int stoi (std::string const & x) { // TODO: Same problem with multiple definitions.
        auto pos = x.find_first_of("eE");
        if (pos == std::string::npos)
            return std::stoi(x);
        return std::stoi(x.substr(0, pos )) * pow10<int>(std::stoi(x.substr(pos + 1, x.size())));
    }

    template <typename t>
    struct registry {
        std::vector<t> container;

        t & push (t && x) {
            container.push_back(std::move(x));
            return container.back();
        }
        t & push (t const & x) {
            container.push_back(x);
            return container.back();
        }

        /*template <typename u>
        t & move (u && x) {
            return push(std::move(x));
        }*/
    };

    template <typename t>
    std::vector<t> & push (t && value, std::vector<t> & target) {
        target.push_back(std::forward<t>(value));
        return target;
    }

    template <typename... fs> struct overload: fs... {
        using fs::operator()...;
        /*template <typename... ts>
        auto operator () (ts... params) {
            return overload{}(*this, params...);
        }*/
    };
    template <typename... fs> overload(fs...) -> overload<fs...>;

    //template <typename... ts> using ptype = std::tuple<ts...>;
    //template <typename... ts> using stype = std::variant<ts...>;

    // TODO: Const version
    template <typename... ts, typename callable>
    requires requires (callable f, ts &... elements) { (f(elements), ...); }
    void tuple_foreach (callable f, std::tuple<ts...> & target) {
        std::apply (
            [& f] (ts &... elements) {
                (f(elements), ...);
            },
            target
        );
    }

    //template <typename t> concept range       = requires (t a) { a.begin(); a.end(); };
    template <typename t> concept range       = requires (t a) { *a.begin(); *a.end(); ++a.begin(); };
    template <typename t> concept sized_range = range<t> && requires (t a) { a.size(); };

    template <range t> using range_value_type = std::remove_reference_t<decltype(*declval<t>().begin())>;

    template <typename t, typename u>
    concept range_of = range<t> && std::convertible_to<range_value_type<t>, u>;
    template <typename t, typename u>
    concept sized_range_of = sized_range<t> && std::convertible_to<range_value_type<t>, u>;

    template <typename t, template <typename> typename u>
    concept constrained_range = range<t> && u<range_value_type<t>>::value;
    template <typename t, template <typename> typename u>
    concept constrained_sized_range = sized_range<t> && u<range_value_type<t>>::value;

    template <typename t> concept pointer = std::is_pointer_v<t>;

    namespace detail {
        template <typename, typename...> struct cat;
        template <template <typename...> typename t, typename... ts, typename... us, typename... vs>
        struct cat<t<ts...>, t<us...>, vs...> {
            using type = cat<t<ts..., us...>, vs...>;
        };
        template <template <typename...> typename t, typename... ts, typename... us>
        struct cat<t<ts...>, t<us...>> {
            using type = t<ts..., us...>;
        };
        template <typename, typename...> struct extend;
        template <template <typename...> typename t, typename... ts, typename... us>
        struct extend<t<ts...>, us...> {
            using type = t<ts..., us...>;
        };
    }

    template <typename t, typename... us> using cat    = typename detail::cat   <t, us...>::type;
    template <typename t, typename... us> using extend = typename detail::extend<t, us...>::type;

    template <typename f>
    struct lift {
        f function;

        lift (f function): function{function} {}

        template <sized_range t>
        auto operator () (t const & target) {
            std::vector<decltype(function(*target.begin()))> result;
            //result.reserve(target.size());
            std::transform(target.begin(), target.end(), std::back_inserter(result), function);
            return result;
        }

        //...
    };

    // TODO: Const version.
    template <sized_range t> requires requires (t a) { **a.begin(); }
    struct reference_view {
        // Only a minimal implementation, that is needed in this project.
        // This may not work properly with some standard algorithms.
        // reference_view is only a (sized) range (not a container) and the iterator satisfies only the basic "iterator" requirement.

        using raw_iterator = decltype(std::declval<t>().begin());
        using reference    = decltype(**std::declval<raw_iterator>());

        struct iterator {
            iterator (raw_iterator raw): raw{raw} {}
            iterator & operator ++ () { ++raw; return *this; }
            reference  operator *  () { return **raw; }
            bool operator == (iterator const & other) const { return raw == other.raw; }
            //bool operator != (iterator const & other) { return !(*this == other); }
        private:
            raw_iterator raw;
        };

        reference_view (t & target): target{target} {}

        iterator begin () { return target.begin(); }
        iterator end   () { return target.end(); }
        iterator begin () const { return target.begin(); }
        iterator end   () const { return target.end(); } // TODO

        std::size_t size () const { return target.size(); }

    private:
        t & target;
    };

    //template <sized_range t> requires requires (t a) { {*a.begin()} -> std::same_as<std::string &>; }
    //template <sized_range_of<std::string> t>
    template <sized_range t>
    std::string join (std::string const & delim, t const & pieces) {
        if (!pieces.size()) return "";
        std::size_t size = 1;
        for (auto const & piece : pieces)
            size += piece.size();
        size += (pieces.size() - 1) * delim.size();
        std::vector<char> result;
        result.reserve(size);
        for (auto it = pieces.begin(); it != pieces.end() - 1; ++it) {
            auto const & piece = *it;
            result.insert(result.end(), piece.data(), piece.data() + piece.size());
            result.insert(result.end(), delim.data(), delim.data() + delim.size());
        }
        auto const & last = *(pieces.end() - 1);
        result.insert(result.end(), last.data(), last.data() + last.size());
        result.push_back('\0');
        return {result.data()};
    }
}
