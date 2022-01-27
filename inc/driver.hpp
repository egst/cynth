#pragma once

#include <type_traits>

#include "config.hpp"

// TODO?
//#include "util/driver_tools.hpp"

#if CTH_DRIVERAPI == CTH_DRIVERAPI_STDOUT

#include "api/stdout/driver.hpp"

#elif CTH_DRIVERAPI == CTH_DRIVERAPI_ASIO

#define IEEE754_64FLOAT 1 // TODO: For some reason, this must be explicitly defined for ASIO. Is this the indended behaviour though?
#include "api/asio/driver.hpp"

#endif

namespace cynth {

    using Driver = std::conditional_t<
        driverApi == DriverApi::asio,
        cynth::driver::asio,
        cynth::driver::stdout
    >;

}
