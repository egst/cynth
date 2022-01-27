#pragma once

#include <string>

#include "asio.h"

namespace cynth::asio {

    enum struct Status {
        ok,               // This value will be returned whenever the call succeeded.
        success,	      // Unique success return value for ASIOFuture calls.
        notPresent,       // Hardware input or output is not present or available.
        hwMalfunction,    // Hardware is malfunctioning (can be returned by any ASIO function).
        invalidParameter, // Input parameter invalid.
        invalidMode,      // Hardware is in a bad mode or used in a bad mode.
        spNotAdvancing,   // Hardware is not running when sample position is inquired.
        noClock,          // Sample clock or rate cannot be determined or is not present.
        noMemory          // Not enough memory for completing the request.
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
        default:
            return "Unknown error.";
        }
    }

}
