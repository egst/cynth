#pragma once

#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <thread>
//#include <condition_variable>
//#include <mutex>

#include "driver/interface.hpp"

#undef stdout

namespace cynth::driver::stdout {

    struct Controller {
        enum struct Status {
            ok,
            error
        };

        static std::string message (Status e) {
            return e == Status::ok ? "ok" : "error";
        }

        static Status init () { return Status::ok; }

        static Status start () {
            for (Time time = 0; !stopFlag; ++time) {
                Rack::offset = time;
                Rack::eval(time);
                printf("%f %f\n", Rack::outChan1(time), Rack::outChan2(time));
                // Note: The intervals do not correspond to the emulated sample rate.
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            }
            return Status::ok;
        }

        static void stop () {
            stopFlag = true;
        }

        static double sampleRate () noexcept { return 44100; }

        static bool initialized () noexcept { return true; }

    private:
        constexpr static std::size_t delay = 50;

        inline static std::atomic<bool> stopFlag;
    };

}
