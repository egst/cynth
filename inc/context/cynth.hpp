#pragma once

#include <forward_list>
#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>

#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"

#include "sem/compound.hpp"
#include "sem/declarations.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::context {

    struct Cynth {
        using ValueEntry = esl::tiny_vector<sem::Variable>;
        using TypeEntry  = esl::tiny_vector<sem::CompleteType>;

        template <typename T>
        using RefvalContainer = std::forward_list<T>;

        std::unordered_map<std::string, ValueEntry> values;
        std::unordered_map<std::string, TypeEntry>  types;

        Cynth * parent;

        Cynth ();

        Cynth (Cynth const &) = default;
        Cynth (Cynth &&)      = default;

        esl::result<ValueEntry *> insertValue (std::string name, ValueEntry const &);
        esl::result<TypeEntry  *> insertType  (std::string name, TypeEntry  const &);

        ValueEntry * findValueInside (std::string const & name);
        TypeEntry  * findTypeInside  (std::string const & name);
        ValueEntry * findValue       (std::string const & name);
        TypeEntry  * findType        (std::string const & name);

        sem::Capture capture (
            std::vector<std::string> const & names,
            std::vector<std::string> const & typeNames
        ) const;
        // TODO: Implement...

        template <typename Value>
        void initStorage ();

        template <typename Value>
        RefvalContainer<Value> & storedValues ();

        template <typename Value>
        esl::reference_result<Value> storeValue (Value const &);

        static Cynth makeChild ();

    protected:
        std::tuple<
            std::optional<RefvalContainer<sem::ArrayAllocation>>
            // ...
            // For now, only arrays are allocated at compile time.
        > referential;
    };

}
