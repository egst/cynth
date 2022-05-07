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

        constexpr static unsigned delay = 2; // ms

        inline static std::atomic<bool> stop_flag = false;

        inline static void stop () {
            stop_flag = false;
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

        template <typename _ = void>
        inline static bool keyPressed (Key key) requires (platform == Platform::windows) {
            return GetAsyncKeyState(static_cast<int>(key)) & 0x01;
        }

        inline static void start () {
            //toneStart(0);
            int timer = 0;
            while (!stop_flag) {
                int time = driver::Rack::offset;
                int step = time - timer;
                timer = time;
                //printf("%i %i %i\n", time, step);
                //printf("%i\n", *press);
                // Note: Keyboard controls only work on Wnidows currently.
                if constexpr (cynth::platform == Platform::windows) {
                    // "Piano" keys:
                    if      (keyPressed(Key::a)) Controls::toneStart(step, 0);
                    else if (keyPressed(Key::w)) Controls::toneStart(step, 1);
                    else if (keyPressed(Key::s)) Controls::toneStart(step, 2);
                    else if (keyPressed(Key::e)) Controls::toneStart(step, 3);
                    else if (keyPressed(Key::d)) Controls::toneStart(step, 4);
                    else if (keyPressed(Key::f)) Controls::toneStart(step, 5);
                    else if (keyPressed(Key::t)) Controls::toneStart(step, 6);
                    else if (keyPressed(Key::g)) Controls::toneStart(step, 7);
                    else if (keyPressed(Key::y)) Controls::toneStart(step, 8);
                    else if (keyPressed(Key::h)) Controls::toneStart(step, 9);
                    else if (keyPressed(Key::u)) Controls::toneStart(step, 10);
                    else if (keyPressed(Key::j)) Controls::toneStart(step, 11);
                    else if (keyPressed(Key::k)) Controls::toneStart(step, 12);
                    //else                         Controls::toneHold(step);

                    // Modulation keys:
                    if      (keyPressed(Key::n1)) Controls::boolOn(0, true);
                    else if (keyPressed(Key::n2)) Controls::boolOff(0, true);
                    else if (keyPressed(Key::n3)) Controls::boolOn(1, true);
                    else if (keyPressed(Key::n4)) Controls::boolOff(1, true);
                    else if (keyPressed(Key::n5)) Controls::intUp(0, true);
                    else if (keyPressed(Key::n6)) Controls::intDown(0, true);
                    else if (keyPressed(Key::n7)) Controls::intUp(1, true);
                    else if (keyPressed(Key::n8)) Controls::intDown(1, true);
                    else if (keyPressed(Key::n9)) Controls::intUp(2, true);
                    else if (keyPressed(Key::n0)) Controls::intDown(2, true);

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
                        case '1': toneStop(); boolOn(0);   break;
                        case '!': toneStop(); boolOff(0);  break;
                        case '2': toneStop(); boolOn(1);   break;
                        case '@': toneStop(); boolOff(1);  break;
                        case '3': toneStop(); boolOn(2);   break;
                        case '#': toneStop(); boolOff(2);  break;
                        case '4': toneStop(); intUp(0);     break;
                        case '$': toneStop(); intDown(0);   break;
                        case '5': toneStop(); intUp(1);     break;
                        case '%': toneStop(); intDown(1);   break;
                        case '6': toneStop(); intUp(2);     break;
                        case '^': toneStop(); intDown(2);   break;
                        //default:  toneStop();
                        }
                    } else
                        toneStop();
                    */
                }

                if (delay)
                    wait(delay);
            }
        }


    };

}
