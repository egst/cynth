#include <iostream>

#include "driver/controller.hpp"
#include "controls.hpp"
#include "gui.hpp"
#include "keyboard.hpp"
#include "midi.hpp"
#include "synth.hpp"
#include "util.hpp"

//std::signal(SIGINT, [] (int) { ...stop(); });

using namespace cynth;
using driver::Time;
using Status = driver::Controller::Status;

int main () {

    driver::Rack::eval = [] (driver::Time t) {
        Controls::run(t);
        cth_run(t);
    };

    cth_init();
    Controls::init();
    midi::init();
    driver::Controller::init();
    auto guiHandle = Gui::init();

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

#if 0
            auto size = message.size();
            if (size == 0) return;
            auto status  = message[0];
            auto kind    = messageKind(status);
            auto channel = messageChannel(status);
            std::cout << "channel: " << channel << '\n';
            switch (kind) {
                case Message::noteOff: {
                    if (size < 3) return;
                    std::cout << "note off\n";
                    auto key      = message[1];
                    auto velocity = message[2];
                    std::cout << "key:      " << key << '\n';
                    std::cout << "velocity: " << velocity << '\n';
                    break;
                }
                case Message::noteOn: {
                    if (size < 3) return;
                    std::cout << "note on\n";
                    auto key      = message[1];
                    auto velocity = message[2];
                    std::cout << "key:      " << key << '\n';
                    std::cout << "velocity: " << velocity << '\n';
                    break;
                }
                case Message::polyphonicKeyPressure: {
                    if (size < 3) return;
                    std::cout << "polyphonic key pressure\n";
                    auto key    = message[1];
                    auto amount = message[2];
                    std::cout << "key:      " << key << '\n';
                    std::cout << "amount:   " << amount << '\n';
                    break;
                }
                case Message::controlChange: {
                    if (size < 3) return;
                    std::cout << "control change\n";
                    auto number = message[1];
                    auto value  = message[2];
                    std::cout << "number:   " << number << '\n';
                    std::cout << "value:    " << value << '\n';
                    break;
                }
                case Message::programChange: {
                    if (size < 2) return;
                    std::cout << "program change\n";
                    auto number = message[1];
                    std::cout << "number:   " << number << '\n';
                    break;
                }
                case Message::channelPressure: {
                    if (size < 2) return;
                    std::cout << "channel pressure\n";
                    auto value  = message[1];
                    std::cout << "value:    " << value << '\n';
                    break;
                }
                case Message::pitchBend: {
                    if (size < 3) return;
                    std::cout << "control change\n";
                    auto msb = message[1];
                    auto lsb = message[2];
                    std::cout << "msb:      " << msb << '\n';
                    std::cout << "lsb:      " << lsb << '\n';
                    break;
                }
                case Message::other: {
                    std::cout << "other\n";
                    break;
                }
            }
#endif
