#pragma once

#include "component.hpp"
#include "category_base.hpp"
#include "sem/forward.hpp"
#include "sem/interface_types.hpp"

// Note: Macros are always undefined at the end of the file.
#define TARGET_DECL \
    target_resolution_result resolve_target (bool) const

namespace cynth::sem {

    struct direct_target {
        typed_value & value;

        TARGET_DECL;
    };

    struct subscript_target {
        component        <any_target>      container;
        component_vector <value::complete> location;

        TARGET_DECL;
    };

    namespace detail {

        using any = variant <
            direct_target,
            subscript_target
        >;

    }

    struct any_target: category_base<any_target, detail::any, true> {
        using base = category_base<any_target, detail::any, true>;
        using base::base;
    };

}

#undef TARGET_DECL
