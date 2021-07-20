#pragma once

#include "component.hpp"
#include "category_base.hpp"
#include "asg/forward.hpp"
#include "asg/interface_types.hpp"

namespace cynth::asg {

    struct direct_target {
        typed_value & value;

        target_resolution_result resolve_target (bool) const;
    };

    struct subscript_target {
        component        <any_target>           container;
        component_vector <asg::value::complete> location;

        target_resolution_result resolve_target (bool) const;
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
