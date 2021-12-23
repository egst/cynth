#pragma once

#include <utility>

#include "esl/tiny_vector.hpp"

#include "context/forward.hpp"
#include "interface/nodes.hpp"
#include "sem/declarations.hpp"
#include "sem/compound.hpp"
#include "sem/numeric_types.hpp"
#include "syn/categories/range_declaration.hpp"

namespace cynth::syn::for_nodes {

    struct State {
        using VariableEntry   = std::pair<std::string, sem::Variable>;
        using AllocationEntry = std::pair<std::string, sem::ArrayAllocation *>;

        context::Main &                   ctx;
        esl::tiny_vector<VariableEntry>   variables;
        esl::tiny_vector<AllocationEntry> allocations;
        esl::tiny_vector<std::string>     assignments;     // `cth_int var_e = var_a`
        esl::tiny_vector<std::string>     declarations;    // `cth_int var_i`
        esl::tiny_vector<std::string>     initializations; // `1`
        esl::tiny_vector<std::string>     advancements;    // `var_i += 2`

        bool comptime () const;

        esl::result<void> processAllocations ();
    };

    // This only considers a list of single-valued range declarations.
    using RangeVector = esl::tiny_vector<std::pair<
        sem::CompleteDeclaration, // Iteration variable declaration
        sem::ResolvedValue        // value::Array or a C variable name
    >>;

    // TODO: Implement
    esl::result<std::pair<sem::Integral, RangeVector>> resolveRangeDeclarations (
        context::Main &,
        syn::category::RangeDeclaration
    );

    esl::result<void> processAllocation (
        State &,
        std::string const    & name,
        sem::ArrayAllocation & allocation
    );

    esl::result<void> processRuntimeArray (
        State &,
        std::string       const & name,
        sem::CompleteType const & type,
        std::string       const & value
    );

    esl::result<void> processArray (
        State &,
        std::string        const & name,
        sem::CompleteType  const & type,
        sem::ResolvedValue const & value
    );

    template <typename Body>
    interface::StatementProcessingResult processStatement (
        context::Main                    &,
        category::RangeDeclaration const & declarations,
        Body                       const & body
    );

}
