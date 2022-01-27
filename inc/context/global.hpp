#pragma once

#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

#include "context/forward.hpp"
#include "context/storage.hpp"
#include "sem/numeric_types.hpp"
#include "sem/values.hpp"

namespace cynth::context {

    using sem::Integral;

    // TODO: Global could contain warning and error entries.
    // Currently the whole translation process stops at any error.
    // Maybe I should continue and just accumulate the errors (and warnings)
    // here, in the context structure.
    // Should I incorporate warnings into esl::result?
    // Or should I just insert results directly into the context structure?

    using GlobalStorage = Storage<sem::FunctionDefinition>;

    struct Global: GlobalStorage {
        friend Main;
        friend syn::node::Block;

        struct GeneratorEntry {
            std::string buffer;
            Integral    size;
            std::string function;
            bool time;
            std::string closure;
        };

        struct FunctionId {
            std::string name;
            std::string closureType;
        };

        inline std::size_t nextId () {
            return id++;
        }

        void insertInclude        (std::string const &);
        void insertType           (std::string const &);
        void insertDependantType  (std::string const &); // These might depend on other types from `types`.
        void insertAllocation     (std::string const &);
        void insertFunction       (std::string const &);
        void insertInitialization (std::string const &);

        /** Instantiate a specific version of a type template. */
        template <typename T>
        std::string instantiateType (T const &);

        void registerGenerator (std::string const & buffer, Integral size, std::string const & function, bool time, std::string const & closure);

        inline std::vector<GeneratorEntry> const & getGenerators () {
            return generators;
        }

    protected:
        std::size_t id = 0;

        std::vector<std::string>        includes;
        std::vector<std::string>        types;
        std::vector<std::string>        dependantTypes;
        std::vector<std::string>        functions;
        std::vector<std::string>        data;
        std::vector<std::string>        initializations;
        std::unordered_set<std::string> instantiated;
        std::vector<GeneratorEntry>     generators;
    };

}
