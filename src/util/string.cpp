#include "util/string.hpp"

#include "config.hpp"
#include "util/math.hpp"

#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>

namespace cynth {

    std::string util::parenthesized (std::string const & str) {
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

    std::string util::trim (std::string const & str) {
        return str.substr(1, str.size() - 2);
    }

    integral util::stoi (std::string const & str) {
        auto pos = str.find_first_of("eE");
        if (pos == std::string::npos)
            return std::stoi(str);
        return std::stoi(str.substr(0, pos )) * util::pow10<int>(std::stoi(str.substr(pos + 1, str.size())));
    }

    std::string util::pretty (std::string const & str) {
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

        return util::join("\n", result);
    }
}
