#pragma once

#include <string>
#include <unordered_map>

#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"

#include "sem/compound.hpp"
#include "sem/types.hpp"

namespace cynth::context {

    struct Lookup {
        using ValueEntry = esl::tiny_vector<sem::Variable>;
        using TypeEntry  = esl::tiny_vector<sem::CompleteType>;

        std::unordered_map<std::string, ValueEntry> values;
        std::unordered_map<std::string, TypeEntry>  types;

        Lookup * parent;

        Lookup ();

        Lookup (Lookup const &) = default;
        Lookup (Lookup &&)      = default;

        esl::result<ValueEntry *> insertValue (std::string name, ValueEntry const &);
        //esl::result<ValueEntry *> insertValue (std::string name, ValueEntry &&);
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

        Lookup makeChild ();

    protected:
    };

}
