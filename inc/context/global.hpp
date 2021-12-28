#pragma once

#include <forward_list>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

#include "context/forward.hpp"
#include "sem/values.hpp"

namespace cynth::context {

    // TODO: Global could contain warning and error entries.
    // Currently the whole translation process stops at any error.
    // Maybe I should continue and just accumulate the errors (and warnings)
    // here, in the context structure.
    // Should I incorporate warnings into esl::result?
    // Or should I just insert results directly into the context structure?

    struct Global {
        friend Main;

        template <typename T>
        using RefvalContainer = std::forward_list<T>;

        std::size_t nextId ();

        void insertAllocation (std::string const &);
        void insertFunction   (std::string const &);
        void insertType       (std::string const &);

        template <typename Value>
        Value & storeValue (Value const &);

        template <typename Value>
        RefvalContainer<Value> & storedValues ();

        /** Instantiate a specific version of a template. */
        template <typename T>
        std::string instantiate (T const &);

        /** Define a function based on its metadata. */
        std::string defineFunction (sem::FunctionDefinition &);
        // TODO: Don't forget to set the newly generated name in the passed function's definition.

        void registerGenerator (std::string const & buffer, std::string const & function, bool time);

    protected:
        std::size_t id = 0;

        std::vector<std::string> types;

        struct {
            std::vector<std::string> declarations;
            std::vector<std::string> definitions;
        } functions;

        struct GeneratorEntry {
            std::string buffer;
            std::string function;
            bool time;
        };

        std::vector<GeneratorEntry> generators;

        struct {
            std::unordered_set<std::string> arrayTypes;  // cth_arr$16$const_int
            std::unordered_set<std::string> bufferTypes; // cth_buff$64
            std::unordered_set<std::string> tupleTypes;  // cth_tup$int$const_float$struct_foo$...
            // ... TODO: The same for internal operations.
        } instantiated;

        // Static lifetime allocations
        std::vector<std::string> data;

        // Static lifetime compile-time storage:
        std::tuple<
            std::optional<RefvalContainer<sem::FunctionDefinition>>
            // ...
        > referential;
    };

}
