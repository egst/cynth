#pragma once

/**
 *  The following macros are defined in the makefile:
 *  CTH_PLATFORM
 *  CTH_DRIVERAPI
 *  CTH_SYNTHOUT
 *
 *  Their intended use-case is conditional header inclusion.
 *  When possible, use the corresponding constexpr bool values defined in this file.
 *
 *  Some default values are defined in compile_flags.txt for the clangd language server.
 */

#define CTH_PLATFORM_WINDOWS 1
#define CTH_PLATFORM_LINUX   2
#define CTH_DRIVERAPI_STDOUT 1
#define CTH_DRIVERAPI_ASIO   2
#define CTH_SYNTHOUT_DEBUG   1
#define CTH_SYNTHOUT_STAT    2
#define CTH_SYNTHOUT_DYNAMIC 3

namespace cynth {

    /**
     *  Windows is the main target currently.
     *  Linux is supported with the stdout driver only.
     *  Windows is supported with the ASIO driver.
     *  WASAPI driver support might be added in the future.
     *  OSX (MacOS) might also be supported in the future with ASIO.
     */
    enum struct Platform {
        windows = CTH_PLATFORM_WINDOWS,
        linux   = CTH_PLATFORM_LINUX
        // osx = CTH_PLATFORM_OSX
    };

    /**
     *  asio:   Works on Windows and OSX. Requires a sound-card that supports it.
     *  wasapi: Works on Windows with any soundcard.
     *  stdout: Simply outputs the samples to the standard output. Works on any platform.
     */
    enum struct DriverApi {
        stdout = CTH_DRIVERAPI_STDOUT,
        asio   = CTH_DRIVERAPI_ASIO
        //wasapi = CTH_DRIVERAPI_WASAPI
    };

    /**
     *  debug:   A standalone executable for debugging and testing purposes only.
     *  stat:    A statically linkable binary.
     *  dynamic: A dynamically linkable binary. Not supported yet.
     */
    enum struct SynthOutput {
        debug   = CTH_SYNTHOUT_DEBUG,
        stat    = CTH_SYNTHOUT_STAT,
        dynamic = CTH_SYNTHOUT_DYNAMIC
    };

    constexpr double      sampleRate  = 44.1; // kHz
    constexpr Platform    platform    = static_cast<Platform>(CTH_PLATFORM);
    constexpr DriverApi   driverApi   = static_cast<DriverApi>(CTH_DRIVERAPI);
    constexpr SynthOutput synthOutput = static_cast<SynthOutput>(CTH_SYNTHOUT);

}
