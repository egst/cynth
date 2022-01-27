#include <chrono>
#include <iostream>
#include <thread>
//#include <exception>

#include "config.hpp"
#include "synth.hpp"

#include <csignal> // TODO: Is there a better way to do this in C++?

namespace {
    volatile bool stop = false; // TODO: std::sig_atomic_t?
}
void cth_stop_handler (int _) {
    stop = true;
}

int main () {

    constexpr bool debug = true;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::duration;

    using cynth::sampleRate;

    int    time     = 0;              // samples
    double tickTime = 1 / sampleRate; // ms

    signal(SIGINT, cth_stop_handler);

    cth_init();

    while (!stop) {
        auto start = high_resolution_clock::now();

        cth_run(time);

        ++time;

        auto end = high_resolution_clock::now();

        auto elapsed = duration_cast<milliseconds>(end - start).count();
        auto remains = tickTime - elapsed;
        if (remains > 0)
            std::this_thread::sleep_for(duration<double, std::milli>{remains});
        else if constexpr (debug)
            std::cout << "can't keep up\n";
    }
    
    std::cout << "synth stopped.\n";

    /*
    try {
        api::driver::input = out;

        std::this_thread::sleep_for(std::chrono::seconds{30});

    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
    std::cout << "DONE\n";
    */
}
