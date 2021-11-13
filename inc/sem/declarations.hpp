#pragma once

#include "sem/forward.hpp"
#include "component.hpp"

namespace cynth::sem {

    template <bool Complete>
    struct declaration {
        component_vector<type::any<Complete>> type;
        std::string                           name;
    };

    template struct declaration<true>;
    template struct declaration<false>;

    struct type_decl {
        std::string name;
    };

    template <bool Complete>
    struct range_decl {
        component_vector <declaration<Complete>> declaration;
        component        <value::complete>       range;
    };

}
