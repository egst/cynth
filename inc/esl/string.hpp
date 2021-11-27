#pragma once

#include "esl/ranges.hpp"
#include "esl/math.hpp"

#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>

namespace esl {

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

    // TODO: template <sized_range_of<std::string> T>
    /** Join strings with a delimiter. */
    template <esl::sized_range T>
    std::string join (std::string const & delim, T const & pieces) {
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
