#pragma once

/**
 *  The following relevant macros are defined in the makefile:
 *  CTH_SRATE
 *  CTH_INTEGRAL
 *  CTH_FLOATING
 *
 *  When possible, use the corresponding constexpr bool values or types defined in this file.
 */

#define STRING(x) #x
#define LITERAL(x) STRING(x)

namespace cynth {

    /** Sample rate in kHz */
    constexpr double sampleRate = CTH_SRATE; // kHz

    using Integral = CTH_INTEGRAL;
    using Floating = CTH_FLOATING;

    constexpr char const * integral = LITERAL(CTH_INTEGRAL);
    constexpr char const * floating = LITERAL(CTH_FLOATING);

}

#undef STRING
#undef LITERAL
