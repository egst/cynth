#pragma once

#include <cstddef>
#include <forward_list>
#include <optional>
#include <string>
#include <vector>

#include "context/forward.hpp"
#include "sem/values.hpp"

namespace cynth::context {

    struct Function {
        friend Main;

        template <typename T>
        using RefvalContainer = std::forward_list<T>;

        /** Run-time allocation. */
        void insertAllocation (std::string);

        /** Compile-time allocation. */
        template <typename Value>
        Value & storeValue (Value const &);

        template <typename Value>
        RefvalContainer<Value> & storedValues ();

    protected:
        //std::size_t id = 0; // Unused, for now.

        // Function lifetime run-time allocations:
        std::vector<std::string> data;

        // Function lifetime compile-time storage:
        std::tuple<
            RefvalContainer<sem::ArrayAllocation>
            // ...
        > referential;
    };

}
