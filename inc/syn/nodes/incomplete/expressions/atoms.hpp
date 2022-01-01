#pragma once

#include <string>

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"
#include "sem/numeric_types.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /**
     *  true
     *  false
     */
    struct Bool {
        bool value;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** 12.34e-56 */
    struct Float {
        sem::Floating value;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** 12e-34 */
    struct Int {
        sem::Integral value;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a */
    struct Name {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        esl::component<std::string> name;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::TargetResolutionResult     resolveTarget     (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** "abc" */
    struct String {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        esl::component<std::string> value;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** (a, ...) */
    struct Tuple {
        esl::component_vector<category::Expression> values;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::TargetResolutionResult     resolveTarget     (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

}
