#include <iostream>

#include "driver/controller.hpp"
#include "controls.hpp"
#include "gui.hpp"
#include "keyboard.hpp"
#include "synth.hpp"
#include "util.hpp"

//std::signal(SIGINT, [] (int) { ...stop(); });

int main () {
    using namespace cynth;
    using driver::Sample;
    using driver::Time;
    using Status = driver::Controller::Status;
    using cynth::sampleRate;

    driver::Rack::eval = [] (driver::Time t) {
        cth_run(t);
    };

    auto guiHandle = Gui::init();
    Controls::init();
    cth_init();
    driver::Controller::init();

    wait(1000); // TODO: GetAsyncKey does some weird stuff at the beginning.
    auto keyboard = makeThread<void>(Keyboard::start);
    keyboard.thread.detach();

    auto controller = makeThread<Status>(driver::Controller::start);
    controller.thread.detach();

    Gui::start();

    Keyboard::stop();
    //driver::Controller::stop();
    Status status = controller.result.get();

    if (controller.thread.joinable()) controller.thread.join();
    if (keyboard.thread.joinable())   keyboard.thread.join();

    if (status != Status::ok) {
        std::cout << "Synthesizer finished with an error.\n";
        //std::cout << static_cast<int>(status) << '\n';
        //std::cout << driver::Controller::message(status) << '\n';
        return static_cast<int>(status);
    }

    std::cout << "Synthesizer finished successfully.\n";
    return 0;

}
