#include "context/function.hpp"

namespace cynth::context {

    void Function::insertAllocation (std::string const & code) {
        if (code.empty()) return;
        data.push_back(code);
    }

    void Function::insertParameter (std::string const & code) {
        if (code.empty()) return;
        parameters.push_back(code);
    }

}
