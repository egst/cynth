#include <cstddef>
#include <iostream>
#include <string>
#include <atomic>

#include "libremidi/libremidi.hpp"

#include "controls.hpp"

namespace cynth {

    struct midi {
        using message_type = libremidi::message_type;

        inline static libremidi::midi_in input = {};

        inline static std::string messageTypeName (message_type type) {
            switch (type) {
                case message_type::INVALID:          return "INVALID";
                // Standard Messages:
                case message_type::NOTE_OFF:         return "NOTE_OFF";
                case message_type::NOTE_ON:          return "NOTE_ON";
                case message_type::POLY_PRESSURE:    return "POLY_PRESSURE";
                case message_type::CONTROL_CHANGE:   return "CONTROL_CHANGE";
                case message_type::PROGRAM_CHANGE:   return "PROGRAM_CHANGE";
                case message_type::AFTERTOUCH:       return "AFTERTOUCH";
                case message_type::PITCH_BEND:       return "PITCH_BEND";
                // System Common Messages:
                case message_type::SYSTEM_EXCLUSIVE: return "SYSTEM_EXCLUSIVE";
                case message_type::TIME_CODE:        return "TIME_CODE";
                case message_type::SONG_POS_POINTER: return "SONG_POS_POINTER";
                case message_type::SONG_SELECT:      return "SONG_SELECT";
                case message_type::RESERVED1:        return "RESERVED1";
                case message_type::RESERVED2:        return "RESERVED2";
                case message_type::TUNE_REQUEST:     return "TUNE_REQUEST";
                case message_type::EOX:              return "EOX";
                // System Realtime Messages:
                case message_type::TIME_CLOCK:       return "TIME_CLOCK";
                case message_type::RESERVED3:        return "RESERVED3";
                case message_type::START:            return "START";
                case message_type::CONTINUE:         return "CONTINUE";
                case message_type::STOP:             return "STOP";
                case message_type::RESERVED4:        return "RESERVED4";
                case message_type::ACTIVE_SENSING:   return "ACTIVE_SENSING";
                case message_type::SYSTEM_RESET:     return "SYSTEM_RESET";
                default:                             return "UNKNOWN";
            }
        }

        inline static void init () {
            auto count = input.get_port_count();
            std::size_t chosen = 0;
            if (count == 0) {
                std::cout << "No compatible input MIDI device available.\n";
                return;
            }
            if (count > 1) {
                std::cout << "Choose an input MIDI device from the following list. Enter the corresponding number.\n";
                for (std::size_t i = 0; i < count; ++i) {
                    auto name = input.get_port_name(i);
                    std::cout << i << ": " << name << '\n';
                }
                std::cin >> chosen;
                if (chosen < 0)
                    chosen = 0;
                if (chosen >= count)
                    chosen = count - 1;
            }
            std::cout << "Input MIDI device chosen: " << input.get_port_name(chosen) << '\n';

            input.set_callback([] (libremidi::message const & msg) {
                //auto channel = msg.get_channel();
                auto type = msg.get_message_type();

                /*
                std::cout << "channel:   " << channel << '\n';
                std::cout << "type:      " << midi::messageTypeName(type) << '\n';
                std::cout << "noteState: " << (noteState ? "on" : "off") << '\n';
                */

                switch (type) {
                    case message_type::NOTE_ON: {
                        int note = msg[1];
                        //int velocity = msg[2];
                        Controls::toneStart(note);
                        break;
                    }
                    case message_type::NOTE_OFF: {
                        int note = msg[1];
                        Controls::toneStop(note);
                        break;
                    }
                }
            });

            input.set_error_callback([] (libremidi::midi_error code, std::string_view info) {
                std::cout << "MIDI error:\n";
                std::cout << info << '\n';
            });

            input.open_port(chosen);
        }
    };

}
