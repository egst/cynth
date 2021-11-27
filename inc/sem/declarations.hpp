#pragma once

#include "sem/forward.hpp"
#include "component.hpp"

namespace cynth::sem {

    template <bool Complete>
    struct Declaration {
        component_vector<type::any<Complete>> type;
        std::string                           name;
    };

    template struct Declaration<true>;
    template struct Declaration<false>;

    struct TypeDecl {
        std::string name;
    };

    template <bool Complete>
    struct RangeDecl {
        component_vector <Declaration<Complete>> declaration;
        component        <value::complete>       range;
    };

}
