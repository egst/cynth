#pragma once

#include "driver/interface.hpp"
#include "config.hpp"

#if CTH_DRIVERAPI == CTH_DRIVERAPI_STDOUT

#include "driver/stdout/controller.hpp"
#define CONTROLLER cynth::driver::stdout::Controller

#elif CTH_DRIVERAPI == CTH_DRIVERAPI_ASIO

//#define IEEE754_64FLOAT 1 TODO: Do I still need this?
#include "driver/asio/controller.hpp"
#define CONTROLLER cynth::driver::asio::Controller

#endif

namespace cynth::driver {

    using Controller = CONTROLLER;

    static_assert(interface::controller<Controller>);

}

#undef CONTROLLER
