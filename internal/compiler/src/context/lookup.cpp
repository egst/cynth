#include "context/lookup.hpp"

namespace cynth::context {

    /*
    esl::reference_result<Lookup::ValueEntry> Lookup::insertValue (std::string const & name, ValueEntry const & entry) {
        if (findValueInside(name))
            return esl::result_error{"Cannot redefine a value in the same scope."};
        return values.insert({name, entry}).first->second;
    }
    */

    esl::reference_result<Lookup::ValueEntry> Lookup::insertValue (std::string const & name, ValueEntry && entry) {
        if (findValueInside(name))
            return esl::result_error{"Cannot redefine a value in the same scope."};
        return values.insert({name, std::move(entry)}).first->second;
    }

    esl::reference_result<Lookup::TypeEntry> Lookup::insertType (std::string const & name, TypeEntry const & entry) {
        if (findTypeInside(name))
            return esl::result_error{"Cannot redefine a type in the same scope."};
        return types.insert({name, entry}).first->second;
    }

    Lookup::ValueEntry * Lookup::findValueInside (std::string const & name) {
        auto iter = values.find(name);
        return iter != values.end() ? &iter->second : nullptr;
    }

    Lookup::TypeEntry * Lookup::findTypeInside (std::string const & name) {
        auto iter = types.find(name);
        return iter != types.end() ? &iter->second : nullptr;
    }

    Lookup::ValueEntry * Lookup::findValue (std::string const & name) {
        auto inside = findValueInside(name);
        if (!parent || inside)
            return inside;
        return parent->findValue(name);
    }

    Lookup::TypeEntry * Lookup::findType (std::string const & name) {
        auto inside = findTypeInside(name);
        if (!parent || inside)
            return inside;
        return parent->findType(name);
    }

}
