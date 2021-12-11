#pragma once

#include "esl/component.hpp"

// Circular dependencies:
#include "sem/forward.hpp"

namespace cynth::sem {

    namespace detail::declarations {

        template <bool Complete>
        struct Declaration {
            esl::component_vector<Type<Complete>> type;
            std::string name;
        };

        template <bool Complete>
        struct RangeDeclaration {
            esl::component_vector<Declaration<Complete>> declaration;
            esl::component<CompleteValue> range;
        };

    }

    struct CompleteDeclaration:   detail::declarations::Declaration<true>  {};
    struct IncompleteDeclaration: detail::declarations::Declaration<false> {};

    struct TypeDeclaration {
        std::string name;
    };

    struct CompleteRangeDeclaration:   detail::declarations::RangeDeclaration<true> {};
    struct IncompleteRangeDeclaration: detail::declarations::RangeDeclaration<true> {};

}
