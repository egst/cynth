#include "context/global.hpp"

namespace cynth::context {

    void Global::insertAllocation (std::string const & code) {
        if (code.empty()) return;
        data.push_back(code);
    }

    void Global::insertType (std::string const & code) {
        if (code.empty()) return;
        types.push_back(code);
    }

    void Global::insertFunction (std::string const & def) {
        if (def.empty()) return;
        functions.push_back(def);
    }

    void Global::registerGenerator (std::string const & buff, std::string const & fun, bool time) {
        generators.emplace_back(buff, fun, time);
    }

    template <typename T>
    std::string Global::instantiateType (T const & tpl) {
        auto name = tpl.name();
        if (!instantiated.contains(name))
            insertType(tpl.definition());
        return name;
    }

    template std::string Global::instantiateType (tpl::Array  const &);
    template std::string Global::instantiateType (tpl::Buffer const &);
    template std::string Global::instantiateType (tpl::Tuple  const &);

}
