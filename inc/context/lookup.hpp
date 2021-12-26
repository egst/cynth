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

        // TODO: There is some problem with assigning to sem::Variable (hence the rvalue overload).
        //ValueEntry & insertValue (std::string name, ValueEntry const &);
        ValueEntry & insertValue (std::string name, ValueEntry &&);
        TypeEntry  & insertType  (std::string name, TypeEntry  const &);
        // TODO: Check if there is some code remaning that exprects a esl::result.

        ValueEntry & findValueInside (std::string const & name);
        TypeEntry  & findTypeInside  (std::string const & name);
        ValueEntry & findValue       (std::string const & name);
        TypeEntry  & findType        (std::string const & name);

        // TODO: Might be not needed.
        sem::CapturedContext capture (
            std::vector<std::string> const & names,
            std::vector<std::string> const & typeNames
        ) const;
        // TODO: Implement...

        Lookup makeChild ();

    protected:
    };

}
