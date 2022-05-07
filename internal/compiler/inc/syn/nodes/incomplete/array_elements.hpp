#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /** a to b */
    struct RangeTo {
        esl::component<category::Expression> from;
        esl::component<category::Expression> to;

        interface::DisplayResult                display             ()                  const;
        interface::ArrayElementProcessingResult processArrayElement (context::Main   &) const;
        interface::NameExtractionResult         extractNames        (context::Lookup &) const;
        interface::TypeNameExtractionResult     extractTypeNames    (context::Lookup &) const;
    };

    /** a to b by c */
    struct RangeToBy {
        esl::component<category::Expression> from;
        esl::component<category::Expression> to;
        esl::component<category::Expression> by;

        interface::DisplayResult                display             ()                const;
        interface::ArrayElementProcessingResult processArrayElement (context::Main &) const;
        interface::NameExtractionResult         extractNames        (context::Lookup &) const;
        interface::TypeNameExtractionResult     extractTypeNames    (context::Lookup &) const;
    };

    /** ...a */
    struct Spread {
        esl::component<category::Expression> container;

        interface::DisplayResult                display             ()                const;
        interface::ArrayElementProcessingResult processArrayElement (context::Main &) const;
        interface::NameExtractionResult         extractNames        (context::Lookup &) const;
        interface::TypeNameExtractionResult     extractTypeNames    (context::Lookup &) const;
    };

}
