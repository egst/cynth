#include "context/global.hpp"

namespace cynth::context {

    // TODO: Implement the insert* methods once generically and reuse.

    void Global::insertInclude (std::string const & code) {
        if (code.empty()) return;
        types.push_back(code);
    }

    void Global::insertType (std::string const & code) {
        if (code.empty()) return;
        types.push_back(code);
    }

    void Global::insertDependantType (std::string const & code) {
        if (code.empty()) return;
        dependantTypes.push_back(code);
    }

    void Global::insertFunction (std::string const & def) {
        if (def.empty()) return;
        functions.push_back(def);
    }

    void Global::insertAllocation (std::string const & code) {
        if (code.empty()) return;
        data.push_back(code);
    }

    void Global::registerGenerator (std::string const & buff, std::string const & fun, bool time) {
        generators.push_back(GeneratorEntry{buff, fun, time});
    }

    template <typename T>
    std::string Global::instantiateType (T const & tpl) {
        auto name = tpl.name();
        if (!instantiated.contains(name))
            insertDependantType(tpl.definition());
        instantiated.insert(name);
        return name;
    }

    template std::string Global::instantiateType (tpl::Array  const &);
    template std::string Global::instantiateType (tpl::Buffer const &);
    template std::string Global::instantiateType (tpl::Tuple  const &);

}
