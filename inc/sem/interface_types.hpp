#pragma once

#include "config.hpp"
#include "result.hpp"
#include "sem/context_forward.hpp"
#include "sem/forward.hpp"

namespace cynth::sem {

    using common_type_result       = result<complete_type>;
    using conversion_result        = result<complete_value>;
    using decay_result             = complete_type;
    template <typename T>
    using get_result               = result<T>;
    using value_type_result        = complete_type;
    using complete_result          = result<complete_type>;
    using target_resolution_result = result<typed_target_value>;
    using names_result             = std::vector<std::string>;

}
