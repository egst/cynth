#pragma once

#include <variant>

#include "esl/category.hpp"
#include "esl/component.hpp"

#include "interface/forward.hpp"
#include "sem/compound.hpp"
#include "sem/values.hpp"

//#include "sem/types.hpp"

// Note: No macros escape this file.
#define TARGET_INTERFACE \
    interface::TargetResolutionResult resolveTarget (bool) const

namespace cynth::sem {

    namespace target {

        struct Direct {
            TypedResolvedValue & value;

            TARGET_INTERFACE;
        };

        struct Subscript {
            esl::component<Target> container;
            esl::component_vector<CompleteValue> location;

            TARGET_INTERFACE;
        };

    }

    namespace detail::targets {

        using Any = std::variant<
            target::Direct,
            target::Subscript
        >;

    }

    struct Target: esl::category<Target, detail::targets::Any> {
        using base = esl::category<Target, detail::targets::Any>;
        using base::base;
    };

}

#undef TARGET_INTERFACE
