#pragma once

#include "util/general.hpp"
#include "util/config.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace cynth::util {

    /** Add parentheses around unparenthesized string. */
    std::string parenthesized (std::string const & str);

    // TODO: template <sized_range_of<std::string> T>
    /** Join strings with a delimiter. */
    template <util::sized_range T>
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
    std::string trim (std::string const & x);

    /** Parse integral numeric string with the scientific notation. */
    util::integral stoi (std::string const & x);

    std::string pretty (std::string const &);

}
