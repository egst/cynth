#include <exception>
#include <iostream>
#include <chrono>

using namespace cynth;

int main () {
    // ... TODO: Init cynth stuff.

    try {
        api::driver::input = out;

        std::this_thread::sleep_for(std::chrono::seconds{30});

    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
    std::cout << "DONE\n";
}
