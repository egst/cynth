#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <windows.h>
constexpr bool windows = true;
#else
constexpr bool windows = false;
#endif

#include <array>
#include <condition_variable>
#include <csignal>
#include <future>
#include <iostream>
#include <iterator>
#include <mutex>
#include <thread>

#include "driver/controller.hpp"
#include "driver/interface.hpp"
//#include "config.hpp"
#include "synth.hpp"

namespace {

    //constexpr bool debug = true;
    constexpr unsigned delay     = 10;    // Delay for keyboard controlls.
    constexpr unsigned srate     = 41000; // TODO: Config...
    constexpr unsigned step      = srate / delay;

    std::atomic<bool> stop = false;

    // TODO: Atomic?
    std::array<float *, 2> output;
    std::array<bool  *, 3> switches;
    std::array<int   *, 3> knobs;
    //std::array<float *, 3> dials;
    int * press;
    //int * release;
    int * note;
    //float * frequency;

    template <typename Out, typename... In>
    auto threadFunction (auto f) {
        return [f] (std::promise<Out> output, In &&... input) {
            output.set_value(f(std::forward<In>(input)...));
        };
    }

    template <typename Out, typename... In>
    std::tuple<std::thread, std::future<Out>> makeThread (auto f, In &&... input) {
        std::promise<Out> promise;
        std::future<Out>  future = promise.get_future();
        auto thread = std::thread{
            threadFunction<Out>(f),
            std::move(promise),
            std::forward<In>(input)...
        };
        return {std::move(thread), std::move(future)};
    }

    void wait (std::size_t delay) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    void switchOn (std::size_t n) {
        *switches[n] = true;
        printf("[switch %i]: on\n", n + 1);
    }

    void switchOff (std::size_t n) {
        *switches[n] = false;
        printf("[switch %i]: off\n", n + 1);
    }

    void knobUp (std::size_t n) {
        *knobs[n] += 2;
        printf("[knob %i]: %i (+)\n", n + 1, *knobs[n]);
    }

    void knobDown (std::size_t n) {
        *knobs[n] -= 2;
        printf("[knob %i]: %i (-)\n", n + 1, *knobs[n]);
    }

    /*
    void dialUp (std::size_t n) {
        printf("[knob %i]: +0.05\n", n);
        *knobs[n] += 0.05;
    }

    void dialDown (std::size_t n) {
        printf("[knob %i]: -0.05\n", n);
        *knobs[n] -= 0.05;
    }
    */

    constexpr std::array<char const *, 13> notes       = {"C", "C#",   "D",   "D#",  "E",   "F",   "F#",  "G",  "G#",  "A",  "A#",  "B",   "C2"};
    constexpr std::array<float,        13> frequencies = {32.7, 32.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.0, 51.91, 55.0, 58.27, 61.74, 65.41};

    void toneStart (std::size_t n) {
        //printf("[%s]\n", notes[n]);
        if (*press >= 0 && *note == n) { // Hold.
            //printf("hold\n");
            *press += step;
        } else { // Press.
            //printf("press\n");
            *press     = 0;
            //*release   = -1;
            *note      = n;
            //*frequency = frequencies[n];
        }
    }

    void toneStop () {
        /*
        if (upCount < upCheck) return;
        //if (upCount == upDelay) printf("[up]\n");
        *press = -1;
        if (*release < 0)
            *release = 0;
        else
            *release += step;
        */
    }

    enum struct Key {
        shift = 0x10,
        a     = 0x41,
        w     = 0x57,
        s     = 0x53,
        e     = 0x45,
        d     = 0x44,
        f     = 0x46,
        t     = 0x54,
        g     = 0x47,
        y     = 0x59,
        h     = 0x48,
        u     = 0x55,
        j     = 0x4a,
        k     = 0x4b,
        n1    = 0x31,
        n2    = 0x32,
        n3    = 0x33,
        n4    = 0x34,
        n5    = 0x35,
        n6    = 0x36,
        n7    = 0x37,
        n8    = 0x38,
        n9    = 0x39,
        n0    = 0x30,
    };

    bool keyPressed (Key key) {
        return GetAsyncKeyState(static_cast<int>(key)) & 0x01;
    }

    void keyboard () {
        while (!stop) {
            //printf("%i %i\n", *press, *release);
            printf("%i\n", *press);
            // Note: Keyboard controls only work on Wnidows currently.
            // On Linux, only ctrl+c works.
            if constexpr (windows) {
                // "Piano" keys:
                if      (keyPressed(Key::a)) toneStart(0);
                else if (keyPressed(Key::w)) toneStart(1);
                else if (keyPressed(Key::s)) toneStart(2);
                else if (keyPressed(Key::e)) toneStart(3);
                else if (keyPressed(Key::d)) toneStart(4);
                else if (keyPressed(Key::f)) toneStart(5);
                else if (keyPressed(Key::t)) toneStart(6);
                else if (keyPressed(Key::g)) toneStart(7);
                else if (keyPressed(Key::y)) toneStart(8);
                else if (keyPressed(Key::h)) toneStart(9);
                else if (keyPressed(Key::u)) toneStart(10);
                else if (keyPressed(Key::j)) toneStart(11);
                else if (keyPressed(Key::k)) toneStart(12);
                else                         toneStop();

                // Modulation keys:
                if      (keyPressed(Key::n1)) switchOn(0);
                else if (keyPressed(Key::n2)) switchOff(0);
                else if (keyPressed(Key::n3)) switchOn(1);
                else if (keyPressed(Key::n4)) switchOff(1);
                else if (keyPressed(Key::n5)) knobUp(0);
                else if (keyPressed(Key::n6)) knobDown(0);
                else if (keyPressed(Key::n7)) knobUp(1);
                else if (keyPressed(Key::n8)) knobDown(1);
                else if (keyPressed(Key::n9)) knobUp(2);
                else if (keyPressed(Key::n0)) knobDown(2);

                /*
                if (_kbhit()) {
                    switch (_getch()) {
                    case 'a': toneStart(0);              break;
                    case 'w': toneStart(1);              break;
                    case 's': toneStart(2);              break;
                    case 'e': toneStart(3);              break;
                    case 'd': toneStart(4);              break;
                    case 'f': toneStart(5);              break;
                    case 't': toneStart(6);              break;
                    case 'g': toneStart(7);              break;
                    case 'y': toneStart(8);              break;
                    case 'h': toneStart(9);              break;
                    case 'u': toneStart(10);             break;
                    case 'j': toneStart(11);             break;
                    case 'k': toneStart(12);             break;
                    case '1': toneStop(); switchOn(0);   break;
                    case '!': toneStop(); switchOff(0);  break;
                    case '2': toneStop(); switchOn(1);   break;
                    case '@': toneStop(); switchOff(1);  break;
                    case '3': toneStop(); switchOn(2);   break;
                    case '#': toneStop(); switchOff(2);  break;
                    case '4': toneStop(); knobUp(0);     break;
                    case '$': toneStop(); knobDown(0);   break;
                    case '5': toneStop(); knobUp(1);     break;
                    case '%': toneStop(); knobDown(1);   break;
                    case '6': toneStop(); knobUp(2);     break;
                    case '^': toneStop(); knobDown(2);   break;
                    //default:  toneStop();
                    }
                } else
                    toneStop();
                */
            }

            wait(delay);
        }
    }

}

int main () {
    using namespace cynth;
    using driver::Sample;
    using driver::Time;
    using Status = driver::Controller::Status;

    // TODO...
    //using cynth::sampleRate;

    // Select controls with special names:
    output = {
        cth_output_buffer("out1"),
        cth_output_buffer("out2"),
    };
    switches = {
        cth_input_bool("switch1"),
        cth_input_bool("switch2"),
        cth_input_bool("switch3"),
    };
    knobs = {
        cth_input_int("knob1"),
        cth_input_int("knob2"),
        cth_input_int("knob3"),
    };
    /*
    dials = {
        cth_input_float("dial1"),
        cth_input_float("dial2"),
        cth_input_float("dial3"),
    };
    */
    press   = cth_input_int("press");
    //release = cth_input_int("release");
    note    = cth_input_int("note");
    //frequency = cth_input_float("freq");

    // Direct empty contols somewhere to avoid checking their presence before every write:
    bool  nullBool;
    int   nullInt;
    float nullFloat;
    for (auto & sw:   switches) if (!sw)   sw   = &nullBool;
    for (auto & knob: knobs)    if (!knob) knob = &nullInt;
    //for (auto & dial: dials)    if (!dial) dial = &nullFloat;
    if (!press)   press   = &nullInt;
    //if (!release) release = &nullInt;
    if (!note)    note    = &nullInt;
    //if (!frequency) frequency = &nullFloat;

    // Default values of controls:
    for (auto & sw:   switches) *sw   = false;
    for (auto & knob: knobs)    *knob = 100;
    //for (auto & dial: dials) *dial = 0.5;
    *press   = 0;
    //*release = 0;
    *note    = 0;
    //*frequency = frequencies[0];

    cth_init();

    driver::Rack::eval = [] (Time t) {
        cth_run(t);
    };

    if (!output[0] && !output[1])
        std::cout << "No output buffer declared. Output will be silent.\n";
    else {
        if (!output[0]) {
            std::cout << "No left channel buffer declared. The right one will be used instead.\n";
            output[0] = output[1];
        }
        if (!output[1]) {
            std::cout << "No right channel buffer declared. The left one will be used instead.\n";
            output[1] = output[0];
        }
        driver::Rack::outChan1 = [] (Time) -> Sample {
            return *output[0];
        };
        driver::Rack::outChan2 = [] (Time) -> Sample {
            return *output[1];
        };
    }

    driver::Controller::init();

    auto [thread, result] = makeThread<Status>(driver::Controller::start);

    thread.detach();

    signal(SIGINT, [] (int) { stop = true; });

    wait(1000); // TODO: GetAsyncKey does some weird stuff at the beginning.
    keyboard();

    driver::Controller::stop();

    Status status = result.get();

    if (thread.joinable())
        thread.join();

    if (status != Status::ok) {
        std::cout << "Synthesizer finished with an error.\n";
        //std::cout << static_cast<int>(status) << '\n';
        //std::cout << driver::Controller::message(status) << '\n';
        return static_cast<int>(status);
    }

    std::cout << "Synthesizer finished successfully.\n";
    return 0;
}
