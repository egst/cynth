#pragma once

/**
 *  The following relevant macros are defined in the makefile:
 *  CTH_PLATFORM
 *  CTH_DRIVER_API
 *  CTH_SRATE
 *  CTH_INTEGRAL
 *  CTH_FLOATING
 *
 *  When possible, use the corresponding constexpr bool values or types defined in this file.
 */

#define CTH_PLATFORM_WIN      1
#define CTH_PLATFORM_LINUX    2
#define CTH_DRIVER_API_STDOUT 1
#define CTH_DRIVER_API_ASIO   2

#define STRING(x) #x
#define LITERAL(x) STRING(x)

// Apparently MS doesn't care about poluting the global namespace... (Or is it a MinGW thing?)
// (Same needs to be done for `interface` in some places.)
#undef stdout

namespace cynth {


    /**
     *  Windows is the main target currently.
     *  Linux is supported with the stdout driver only.
     *  Windows is supported with the ASIO driver.
     *  WASAPI driver support might be added in the future.
     *  OSX (MacOS) might also be supported in the future with ASIO.
     */
    enum struct Platform {
        windows = CTH_PLATFORM_WIN,
        linux   = CTH_PLATFORM_LINUX
        // osx = CTH_PLATFORM_OSX
    };

    /**
     *  asio:   Works on Windows and OSX. Requires a sound-card that supports it.
     *  wasapi: Works on Windows with any soundcard.
     *  stdout: Simply outputs the samples to the standard output. Works on any platform.
     */
    enum struct DriverApi {
        stdout = CTH_DRIVER_API_STDOUT,
        asio   = CTH_DRIVER_API_ASIO
        //wasapi = CTH_DRIVER_API_WASAPI
    };

    /** Sample rate in kHz */
    constexpr double    sampleRate = CTH_SRATE; // kHz
    constexpr Platform  platform   = static_cast<Platform>(CTH_PLATFORM);
    constexpr DriverApi driverApi  = static_cast<DriverApi>(CTH_DRIVER_API);

    using Integral = CTH_INTEGRAL;
    using Floating = CTH_FLOATING;

    constexpr char const * integral = LITERAL(CTH_INTEGRAL);
    constexpr char const * floating = LITERAL(CTH_FLOATING);

}

#undef STRING
#undef LITERAL
