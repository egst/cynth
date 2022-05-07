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

        /** Creates the root context. */
        inline Lookup (): parent{nullptr} {}

        inline Lookup (Lookup const &) = default;
        inline Lookup (Lookup &&)      = default;

        // TODO: There is some problem with assigning to sem::Variable (hence the rvalue overload).
        //esl::reference_result<ValueEntry> insertValue (std::string name, ValueEntry const &);
        esl::reference_result<ValueEntry> insertValue (std::string const & name, ValueEntry &&);
        esl::reference_result<TypeEntry>  insertType  (std::string const & name, TypeEntry const &);

        ValueEntry * findValue (std::string const & name);
        TypeEntry  * findType  (std::string const & name);

        /** Creates a context for a nested scope. */
        inline Lookup makeChild () {
            return {this};
        }

    protected:
        Lookup * parent;

        std::unordered_map<std::string, ValueEntry> values;
        std::unordered_map<std::string, TypeEntry>  types;

        inline Lookup (Lookup * parent): parent{parent} {}

        ValueEntry * findValueInside (std::string const & name);
        TypeEntry  * findTypeInside  (std::string const & name);
    };

}
