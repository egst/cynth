#pragma once

#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

#include "context/forward.hpp"
#include "context/storage.hpp"
#include "sem/values.hpp"

namespace cynth::context {

    // TODO: Global could contain warning and error entries.
    // Currently the whole translation process stops at any error.
    // Maybe I should continue and just accumulate the errors (and warnings)
    // here, in the context structure.
    // Should I incorporate warnings into esl::result?
    // Or should I just insert results directly into the context structure?

    using GlobalStorage = Storage<sem::FunctionDefinition>;

    struct Global: GlobalStorage {
        friend Main;

        struct GeneratorEntry {
            std::string buffer;
            std::string function;
            bool time;
        };

        struct FunctionId {
            std::string name;
            std::string closureType;
        };

        inline std::size_t nextId () {
            return id++;
        }

        void insertAllocation (std::string const &);
        void insertType       (std::string const &);

        /** Instantiate a specific version of a type template. */
        template <typename T>
        std::string instantiateType (T const &);

        void registerGenerator (std::string const & buffer, std::string const & function, bool time);

        void insertFunction (std::string const &);

    protected:
        std::size_t id = 0;

        // Static lifetime allocations
        std::vector<std::string> data;

        std::vector<std::string> types;

        std::vector<std::string> functions;

        std::vector<GeneratorEntry> generators;

        std::unordered_set<std::string> instantiated;
    };

}
