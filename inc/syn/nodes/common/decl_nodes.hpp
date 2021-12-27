#pragma once

#include "esl/result.hpp"

#include "context/main.hpp"
#include "interface/nodes.hpp"
#include "sem/values.hpp"
#include "sem/declarations.hpp"
#include "syn/categories/expression.hpp"

namespace cynth::syn::decl_nodes {

    esl::result<void> define (
        context::Main &,
        esl::tiny_vector<sem::CompleteDeclaration> const &,
        esl::tiny_vector<sem::ResolvedValue>       const &
    );

}
