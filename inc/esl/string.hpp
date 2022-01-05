#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

#include "esl/concepts.hpp"
#include "esl/math.hpp"
#include "esl/ranges.hpp"
#include "esl/type_manip.hpp"

namespace esl {

    inline std::vector<std::string> split (std::string delim, std::string const & str) {
        std::vector<std::string> result;
        std::size_t last = 0;
        std::size_t next = 0;
        while ((next = str.find(delim, last)) != std::string::npos) {
            result.push_back(str.substr(last, next - last));
            last = ++next;
        }
        result.push_back(str.substr(last));
        return result;
    }

    /** Add parentheses around unparenthesized string. */
    inline std::string parenthesized (std::string const & str) {
        if (str.front() != '(' || str.back() != ')')
            return "(" + str + ")";

        int state = 0;
        for (std::size_t i = 1; i < str.size() - 1; ++i) {
            char const & c = str[i];
            if (c == '(')
                ++state;
            if (c == ')')
                --state;
            if (state < 0)
                return "(" + str + ")";
        }

        return str;
    }

    inline std::string repeat (std::string const & str, std::size_t count) {
        if (count == 0)
            return str;
        std::string result;
        result.reserve(str.size() * count);
        while (count--)
            result += str;
        return result;
    }

    /** Join strings with a delimiter. */

    namespace detail::string {

        template <typename... Ts>
        decltype(auto) last(Ts &&... vals){
           return (std::forward<Ts>(vals), ...);
        }

        inline auto make_string (char const * str) {
            return std::string_view{str};
        }

        inline auto const & make_string (std::string const & str) {
            return str;
        }

        template <esl::sized_range R, std::convertible_to<std::string>... Ts>
        requires (std::convertible_to<esl::range_value_type<R>, std::string>)
        std::string join (
            std::string const & delim,
            R const & pieces_range,
            Ts const &... piece_vals
        ) {
            std::size_t range_count = pieces_range.size();
            constexpr std::size_t vals_count = sizeof...(Ts);
            std::size_t count = vals_count + range_count;
            if (count == 0) return "";

            std::size_t size = 1;
            ((size += make_string(piece_vals).size()), ...);
            for (auto const & piece: pieces_range)
                size += make_string(piece).size();
            size += (count - 1) * delim.size();

            std::vector<char> result;
            result.reserve(size);

            // Welp, this looks crazy...
            // but I guess that's the simplest way to to it without introducing even more helper functions.
            {
                std::size_t i = 0;
                ((
                    i < vals_count - (range_count == 0) ? (
                        // do this for every value frow `piece_vals...` but the last one (if there are no more values in `pieces_range`)
                        result.insert(result.end(), make_string(piece_vals).data(), make_string(piece_vals).data() + make_string(piece_vals).size()),
                        result.insert(result.end(), delim.data(), delim.data() + delim.size()),
                        0
                    ) : 0,
                    ++i
                ), ...);
            }
            // the same thing with the dynamc range:
            for (auto it = pieces_range.begin(); it != pieces_range.end() - 1; ++it) {
                auto const & piece = make_string(*it);
                result.insert(result.end(), piece.data(), piece.data() + piece.size());
                result.insert(result.end(), delim.data(), delim.data() + delim.size());
            }

            if constexpr (vals_count > 0) {
                if (range_count == 0) {
                    auto last = detail::string::last(make_string(piece_vals)...);
                    result.insert(result.end(), last.data(), last.data() + last.size());
                } else {
                    auto const & last = make_string(*(pieces_range.end() - 1));
                    result.insert(result.end(), last.data(), last.data() + last.size());
                }
            } else {
                auto const & last = make_string(*(pieces_range.end() - 1));
                result.insert(result.end(), last.data(), last.data() + last.size());
            }

            result.push_back('\0');
            return {result.data()};
        }

        template <typename... Ts, size_t... Is>
        auto join_tup (std::string const & delim, std::tuple<Ts...> args, std::index_sequence<Is...>) {
            constexpr auto last = sizeof...(Ts) - 1;
            if constexpr (std::convertible_to<esl::last<Ts...>, std::string>)
                return detail::string::join(delim, esl::nullrange<std::string>{}, std::get<Is>(args)..., std::get<last>(args));
            else
                return detail::string::join(delim, std::get<last>(args), std::get<Is>(args)...);
        }

    }

    template <typename... Ts>
    auto join (std::string const & delim, Ts &&... args) {
        if constexpr (sizeof...(args) > 0)
            return detail::string::join_tup(delim, std::forward_as_tuple(args...), std::make_index_sequence<sizeof...(args) - 1>{});
        else
            return detail::string::join(delim, esl::nullrange<std::string>{});
    }

    /** Trim the first and last characters of a string. Used to remove parentheses. */
    inline std::string trim (std::string const & str) {
        return str.substr(1, str.size() - 2);
    }

    namespace detail::string {

        template <typename T>
        T std_stoi (std::string const & str) {
            return std::stoi(str);
        }

        template <> inline int       std_stoi (std::string const & str) { return std::stoi(str);  }
        template <> inline long      std_stoi (std::string const & str) { return std::stol(str);  }
        template <> inline long long std_stoi (std::string const & str) { return std::stoll(str); }

    }

    /** Parse integral numeric string with the scientific notation. */
    template <typename T>
    T stoi (std::string const & str) {
        auto pos = str.find_first_of("eE");
        if (pos == std::string::npos)
            return std::stoi(str);
        return detail::string::std_stoi<T>(str.substr(0, pos )) * esl::pow10<T>(std::stoi(str.substr(pos + 1, str.size())));
    }

    inline std::string indent (std::string const & indentation, std::string const & newline, std::string const & str) {
        auto lines = esl::split(newline, str);
        if (lines.size() < 2) { // Just a small optimization to avoid more allocations.
            return indentation + str;
        }
        std::vector<std::string> result;
        for (auto const & line: lines) {
            result.push_back(indentation + line);
        }
        return esl::join(newline, result);
    }

    inline std::string reindent (std::size_t strip, std::string const & indentation, std::string const & newline, std::string const & str) {
        auto lines = esl::split(newline, str);
        if (lines.size() < 2) { // Just a small optimization to avoid more allocations.
            return indentation + str.substr(std::min(strip, str.size()));
        }
        std::vector<std::string> result;
        for (auto const & line: lines) {
            result.push_back(indentation + line.substr(std::min(strip, line.size())));
        }
        return esl::join(newline, result);
    }

    // TODO: Support other indentation and new line characters.
    inline std::string pretty (std::string const & str) {
        std::size_t const line_count = std::count(str.begin(), str.end(), '\n') + 1;
        std::vector<std::string> result;
        result.reserve(line_count);

        std::size_t indent      = 0;
        std::size_t next_indent = 0;
        std::string::const_iterator line_begin = str.begin();
        for (auto it = str.begin(); it <= str.end(); ++it) { // Including .end() intentionally to reach the \0 character.
            switch (*it) {
            case '{':
                ++next_indent;
                break;
            case '}':
                indent = --next_indent;
                break;
            case '\n':
            case '\0':
                std::string const line = str.substr(line_begin - str.begin(), it - line_begin);
                if (line.empty())
                    result.push_back("");
                else
                    result.push_back(std::string(indent, '\t') + line);
                line_begin = it + 1;
                indent = next_indent;
            }
        }

        return esl::join("\n", result);
    }

}
