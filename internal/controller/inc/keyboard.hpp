#pragma once

#include <csignal>
#include <cstdio>

#include <array>
#include <atomic>
#include <iostream>

#include "driver/controller.hpp"
#include "driver/interface.hpp"
#include "config.hpp"
#include "controls.hpp"
#include "util.hpp"

#if CTH_PLATFORM == CTH_PLATFORM_WIN
//#include <conio.h>
#include <windows.h>
#endif

namespace cynth {

    struct Keyboard {

        constexpr static Integral noteBase = 60;

        constexpr static unsigned delay = 2; // ms

        inline static std::atomic<bool> stopFlag = false;

        inline static void stop () {
            stopFlag = false;
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
            z     = 0x5a,
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

        template <typename _ = void>
        inline static bool keyPressed (Key key) requires (platform == Platform::windows) {
            return GetAsyncKeyState(static_cast<int>(key)) & 0x01;
        }

        inline static void start () {
            while (!stopFlag) {
                // Note: Keyboard controls only work on Wnidows currently.
                if constexpr (cynth::platform == Platform::windows) {
                    // "Piano" keys:
                    if      (keyPressed(Key::a)) Controls::toneStart(noteBase + 0);
                    else if (keyPressed(Key::w)) Controls::toneStart(noteBase + 1);
                    else if (keyPressed(Key::s)) Controls::toneStart(noteBase + 2);
                    else if (keyPressed(Key::e)) Controls::toneStart(noteBase + 3);
                    else if (keyPressed(Key::d)) Controls::toneStart(noteBase + 4);
                    else if (keyPressed(Key::f)) Controls::toneStart(noteBase + 5);
                    else if (keyPressed(Key::t)) Controls::toneStart(noteBase + 6);
                    else if (keyPressed(Key::g)) Controls::toneStart(noteBase + 7);
                    else if (keyPressed(Key::y)) Controls::toneStart(noteBase + 8);
                    else if (keyPressed(Key::h)) Controls::toneStart(noteBase + 9);
                    else if (keyPressed(Key::u)) Controls::toneStart(noteBase + 10);
                    else if (keyPressed(Key::j)) Controls::toneStart(noteBase + 11);
                    else if (keyPressed(Key::k)) Controls::toneStart(noteBase + 12);

                    // Modulation keys:
                    if      (keyPressed(Key::n1)) Controls::on(0, true);
                    else if (keyPressed(Key::n2)) Controls::off(0, true);
                    else if (keyPressed(Key::n3)) Controls::on(1, true);
                    else if (keyPressed(Key::n4)) Controls::off(1, true);
                    else if (keyPressed(Key::n5)) Controls::upInt(0, true);
                    else if (keyPressed(Key::n6)) Controls::downInt(0, true);
                    else if (keyPressed(Key::n7)) Controls::upInt(1, true);
                    else if (keyPressed(Key::n8)) Controls::downInt(1, true);
                    else if (keyPressed(Key::n9)) Controls::upInt(2, true);
                    else if (keyPressed(Key::n0)) Controls::downInt(2, true);
                }

                if (delay)
                    wait(delay);
            }
        }


    };

}
