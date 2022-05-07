#include <iostream>

#include "driver/controller.hpp"
#include "gui.hpp"
#include "synth.hpp"
#include "util.hpp"

#include "simple_controls.hpp"

int main () {
    using namespace cynth;
    using driver::Sample;
    using driver::Time;
    using Status = driver::Controller::Status;
    using cynth::sampleRate;
    using Controls = SimpleControls;

    Controls::init();
    cth_init();
    driver::Controller::init();

    auto controllerHandle = makeThread<Status>(driver::Controller::start);
    controllerHandle.thread.detach();

    auto guiHandle = makeThread<void>(Gui::start);
    guiHandle.thread.detach();

    wait(1000); // TODO: GetAsyncKey does some weird stuff at the beginning.
    Controls::keyboard();

    driver::Controller::stop();

    Status status = controllerHandle.result.get();

    if (controllerHandle.thread.joinable()) controllerHandle.thread.join();
    if (guiHandle.thread.joinable())        guiHandle.thread.join();

    if (status != Status::ok) {
        std::cout << "Synthesizer finished with an error.\n";
        //std::cout << static_cast<int>(status) << '\n';
        //std::cout << driver::Controller::message(status) << '\n';
        return static_cast<int>(status);
    }

    std::cout << "Synthesizer finished successfully.\n";
    return 0;
}
