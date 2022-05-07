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
                if (time % (skip + 1) == 0) {
                    Rack::offset = time;
                    Rack::eval(time);
                    printf(
                        "%i %f %f\n",
                        static_cast<int>(time),
                        static_cast<float>(Rack::outChan1(time)),
                        static_cast<float>(Rack::outChan2(time))
                    );
                }
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
        // Wait {delay} ms for the next sample. Skip {skip} samples.
        //constexpr static std::size_t delay = 50;
        constexpr static std::size_t delay = 1;
        //constexpr static std::size_t skip  = 0;
        constexpr static std::size_t skip  = 1000;

        inline static std::atomic<bool> stopFlag;
    };

}
