#pragma once

#include "driver/interface.hpp"
#include "config.hpp"

#if CTH_DRIVER_API == CTH_DRIVER_API_STDOUT

#include "driver/stdout/controller.hpp"
#define CONTROLLER cynth::driver::stdout::Controller

#elif CTH_DRIVER_API == CTH_DRIVER_API_ASIO

//#define IEEE754_64FLOAT 1 TODO: Do I still need this?
#include "driver/asio/controller.hpp"
#define CONTROLLER cynth::driver::asio::Controller

#endif

namespace cynth::driver {

    using Controller = CONTROLLER;

    static_assert(interface::controller<Controller>);

}

#undef CONTROLLER
