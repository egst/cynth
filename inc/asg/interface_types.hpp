#pragma once

#include "config.hpp"
#include "context_forward.hpp"
#include "result.hpp"
#include "asg/forward.hpp"

#include <optional>

namespace cynth::asg {

    using common_type_result       = result<type::complete>;
    using conversion_result        = result<value::complete>;
    using decay_result             = type::complete;
    template <typename T>
    using get_result               = result<T>;
    using value_type_result        = type::complete;
    using complete_result          = result<type::complete>;
    using target_resolution_result = result<typed_target_value>;

}
