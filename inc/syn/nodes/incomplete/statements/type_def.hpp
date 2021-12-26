#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"
#include "syn/nodes/incomplete/types.hpp"

namespace cynth::syn::node {

    /** type T = U */
    struct TypeDef {
        node::TypeName                 target;
        esl::component<category::Type> type;

        interface::DisplayResult             display          ()                const;
        interface::StatementProcessingResult processStatement (context::Main &) const;
    };

}
