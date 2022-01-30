#pragma once

/**
 *  Use this header instead of the `asio.h` header.
 *  For some reason, `asio.h` does not include the `asiosys.h` header that performs setup of system-related macros.
 *  Without it, there might be differences in some header declarations and their correspondig definitions
 *  because, unlike `asio.h`, `asio.cpp` does include `asiosys.h`.
 *
 *  `asiodrivers.h` seems fine, but I'll need to take a closer look.
 */

#include "asiosys.h"
#include "asio.h"
