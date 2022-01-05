#pragma once

namespace cynth {

    enum struct Platform {
        windows,
        linux
    };

    constexpr Platform platform = Platform::linux;

    constexpr double sampleRate = 44.1; // kHz

}
