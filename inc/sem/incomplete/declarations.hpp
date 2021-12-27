#pragma once

#include <string>

#include "esl/component.hpp"

// Circular dependencies:
#include "sem/forward.hpp"

namespace cynth::sem {

    struct CompleteDeclaration {
        esl::component_vector<CompleteType> type;
        std::string name;
    };

    struct IncompleteDeclaration {
        esl::component_vector<IncompleteType> type;
        std::string name;
    };

    struct CompleteRangeDeclaration {
        esl::component_vector<CompleteDeclaration> declaration;
        esl::component<ResolvedValue> range;
    };

    struct IncompleteRangeDeclaration {
        esl::component_vector<IncompleteDeclaration> declaration;
        esl::component<ResolvedValue> range;
    };

    struct TypeDeclaration {
        std::string name;
    };

}
