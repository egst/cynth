#pragma once

/* Local libraries: */
#include "platform.hpp"
//#include "user_library/functions/sequence_function.hpp"

namespace Cynth::UserLibrary::Functions {

    // Forward declaration:
    class SequenceFunction;

    class CYNTH_EXPORT SequenceElement {
    private:
        double duration;
        float freq;
        float amp;

    public:
        SequenceElement(double duration, float amp = 0, float freq = 0);

        friend class SequenceFunction;
    };

}