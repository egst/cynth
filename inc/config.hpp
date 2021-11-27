#pragma once

#include "basic_config.hpp"
#include "util/tiny_vector.hpp"

#include <variant>
#include <vector>
#include <optional>

#include <iostream>

namespace Cynth {

    template <typename T>
    using TupleVector = Util::TinyVector<T>;

}
