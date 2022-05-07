#pragma once

#include <string>

#include "asio.hpp"

namespace cynth::driver::asio {

    enum struct Status {
        // These correspond to ASIOError values:
        ok,               // This value will be returned whenever the call succeeded.
        success,          // Unique success return value for ASIOFuture calls.
        notPresent,       // Hardware input or output is not present or available.
        hwMalfunction,    // Hardware is malfunctioning (can be returned by any ASIO function).
        invalidParameter, // Input parameter invalid.
        invalidMode,      // Hardware is in a bad mode or used in a bad mode.
        spNotAdvancing,   // Hardware is not running when sample position is inquired.
        noClock,          // Sample clock or rate cannot be determined or is not present.
        noMemory,         // Not enough memory for completing the request.
        // These were added:
        failedSetup,
        unsupportedSystem,
        error // A general error - just a fallback case.
    };

    inline Status status (ASIOError error) {
        return static_cast<Status>(error);
    }

    inline std::string errorMessage (Status status) {
        switch (status) {
        case Status::ok:
            return "OK.";
        case Status::success:
            return "Success.";
        case Status::notPresent:
            return "Hardware input or output is not present or available.";
        case Status::hwMalfunction:
            return "Hardware is malfunctioning.";
        case Status::invalidParameter:
            return "Invalid parameter.";
        case Status::invalidMode:
            return "Invalid mode.";
        case Status::spNotAdvancing:
            return "Hardware is not running when sample position is inquired.";
        case Status::noClock:
            return "No clock.";
        case Status::noMemory:
            return "No memory.";
        case Status::failedSetup:
            return "Failed setup.";
        case Status::unsupportedSystem:
            return "Unsupported sytem.";
        default:
            return "Unknown error.";
        }
    }

}
