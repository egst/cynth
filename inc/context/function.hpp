#pragma once

#include <cstddef>
#include <forward_list>
#include <optional>
#include <string>
#include <vector>

#include "context/forward.hpp"
#include "context/storage.hpp"
#include "sem/values.hpp"

namespace cynth::context {

    using FunctionStorage = Storage<sem::ArrayAllocation>;

    struct Function: FunctionStorage {
        friend Main;

        template <typename T>
        using RefvalContainer = std::forward_list<T>;

        /** Run-time allocation. */
        void insertAllocation (std::string const &);

        /** Run-time parameter. */
        void insertParameter (std::string const &); // TODO: Implement.

        inline esl::tiny_vector<std::string> const & getParameters () const {
            return parameters;
        }

    protected:
        //std::size_t id = 0; // Unused, for now.

        // Function lifetime run-time allocations:
        std::vector<std::string> data;

        // Run-time parameter declarations:
        esl::tiny_vector<std::string> parameters;
    };

}
