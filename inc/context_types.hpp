#pragma once

#include "config.hpp"
#include "asg/types.hpp"
#include "asg/values.hpp"

#include <forward_list>

namespace cynth {

    // TODO: Move this to asg::
    using value_vector = tuple_vector<asg::value ::complete>;
    using type_vector  = tuple_vector<asg::type  ::complete>;

    template <typename T>
    using refval_container = std::forward_list<T>;

    struct typed_value {
        value_vector value;
        type_vector  type;
    };

    struct typed_target_value {
        value_vector & value;
        type_vector    type;
    };

}
