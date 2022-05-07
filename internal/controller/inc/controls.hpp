#pragma once

#include <csignal>
#include <cstddef>
#include <cstdio>

#include <array>
#include <atomic>
#include <iostream>
//#include <unordered_map>
#include <map>
#include <vector>

#include "driver/controller.hpp"
#include "driver/interface.hpp"
#include "config.hpp"
#include "synth.hpp"
#include "util.hpp"

namespace cynth {

    struct Controls {

        constexpr static bool     boolDefault = false;
        constexpr static unsigned intDefault  = 0;
        constexpr static unsigned intStep     = 1;

        // TODO: Atomic?
        // TODO: Encapsulate.
        inline static std::vector<Floating       *> outBuffList = {};
        inline static std::vector<bool           *> inBoolList  = {};
        inline static std::vector<Integral       *> inIntList   = {};
        inline static std::vector<bool     const *> outBoolList = {};
        inline static std::vector<Integral const *> outIntList  = {};

        inline static std::map<std::string, Floating       *> outBuffMap = {};
        inline static std::map<std::string, bool           *> inBoolMap  = {};
        inline static std::map<std::string, Integral       *> inIntMap   = {};
        inline static std::map<std::string, bool     const *> outBoolMap = {};
        inline static std::map<std::string, Integral const *> outIntMap  = {};

        inline static Integral * press = nullptr;
        inline static Integral * note  = nullptr;

        inline static bool boolGet (std::size_t n) {
            if (n >= outBoolList.size()) return boolDefault;
            return *outBoolList[n];
        }

        inline static Integral intGet (std::size_t n) {
            if (n >= outIntList.size()) return intDefault;
            return *outIntList[n];
        }

        inline static bool boolGet (std::string const & n) {
            auto it = outBoolMap.find(n);
            if (it == outBoolMap.end()) return boolDefault;
            return *it->second;
        }

        inline static Integral intGet (std::string const & n) {
            auto it = outIntMap.find(n);
            if (it == outIntMap.end()) return intDefault;
            return *it->second;
        }

        inline static void boolSet (std::size_t n, bool val, bool log = false) {
            if (n >= inBoolList.size()) return;
            *inBoolList[n] = val;
            if (log)
                std::printf("[%zu]: %s\n", n + 1, val ? "on" : "off");
        }

        inline static void boolSet (std::string const & n, bool val, bool log = false) {
            auto it = inBoolMap.find(n);
            if (it == inBoolMap.end()) return;
            *it->second = val;
            if (log)
                std::printf("[%s]: %s\n", n.data(), val ? "on" : "off");
        }

        template <typename T>
        static void boolOn (T n, bool log = false) {
            boolSet(n, true, log);
        }

        template <typename T>
        static void boolOff (T n, bool log = false) {
            boolSet(n, false, log);
        }

        inline static void intSet (std::size_t n, Integral val, bool log = false) {
            if (n >= inIntList.size()) return;
            *inIntList[n] = val;
            if (log)
                std::printf("[%zu]: %i\n", n + 1, static_cast<int>(val));
        }

        inline static void intSet (std::string const & n, Integral val, bool log = false) {
            auto it = inIntMap.find(n);
            if (it == inIntMap.end()) return;
            *it->second = val;
            if (log)
                std::printf("[%s]: %i\n", n.data(), static_cast<int>(val));
        }

        inline static void intUp (std::size_t n, bool log = false) {
            if (n >= inIntList.size()) return;
            *inIntList[n] += intStep;
            if (log)
                std::printf("[%zu]: %i\n", n + 1, static_cast<int>(*inIntList[n]));
        }

        inline static void intUp (std::string const & n, bool log = false) {
            auto it = inIntMap.find(n);
            if (it == inIntMap.end()) return;
            *it->second += intStep;
            if (log)
                std::printf("[%s]: %i\n", n.data(), static_cast<int>(*it->second));
        }

        inline static void intDown (std::size_t n, bool log = false) {
            if (n >= inIntList.size()) return;
            *inIntList[n] -= intStep;
            if (log)
                std::printf("[%zu]: %i\n", n + 1, static_cast<int>(*inIntList[n]));
        }

        inline static void intDown (std::string const & n, bool log = false) {
            auto it = inIntMap.find(n);
            if (it == inIntMap.end()) return;
            *it->second -= intStep;
            if (log)
                std::printf("[%s]: %i\n", n.data(), static_cast<int>(*it->second));
        }

        inline static void toneHold (Integral step) {
            *press += step;
        }

        inline static void toneStart (Integral step, std::size_t n) {
            if (*note == n)
                toneHold(step);
            else {
                //std::printf("[%s]\n", notes[n]);
                //std::printf("%i\n", static_cast<int>(step));
                *press = 0;
                *note  = n;
            }
        }

        inline static bool nullBool = false;
        inline static Integral nullInt  = 0;

        static void init () {
            // Select controls with special names:
            outBuffMap = {
                {"out1", cth_output_buffer("out1")},
                {"out2", cth_output_buffer("out2")},
            };
            inBoolMap = {
                {"switch1", cth_input_bool("switch1")},
                {"switch2", cth_input_bool("switch2")},
                {"switch3", cth_input_bool("switch3")},
            };
            inIntMap = {
                {"knob1", cth_input_int("knob1")},
                {"knob2", cth_input_int("knob2")},
                {"knob3", cth_input_int("knob3")},
            };
            /*
            outBoolMap = {
                {"diode1", cth_input_bool("diode1")},
                {"diode2", cth_input_bool("diode2")},
                {"diode3", cth_input_bool("diode3")},
            };
            outIntMap = {
                {"level1", cth_input_int("level1")},
                {"level2", cth_input_int("level2")},
                {"level3", cth_input_int("level3")},
            };
            */
            press = cth_input_int("press");
            note  = cth_input_int("note");

            constexpr auto second = [] (auto p) { return p.second; };
            std::transform(outBuffMap.begin(), outBuffMap.end(), std::back_inserter(outBuffList), second);
            std::transform(inBoolMap.begin(),  inBoolMap.end(),  std::back_inserter(inBoolList),  second);
            std::transform(inIntMap.begin(),   inIntMap.end(),   std::back_inserter(inIntList),   second);
            std::transform(outBoolMap.begin(), outBoolMap.end(), std::back_inserter(outBoolList), second);
            std::transform(outIntMap.begin(),  outIntMap.end(),  std::back_inserter(outIntList),  second);

            // Direct empty controls somewhere to avoid checking their presence before every write:
            for (auto & p: inBoolList) if (!p) p = &nullBool;
            for (auto & p: inIntList)  if (!p) p = &nullInt;
            if (!press) press = &nullInt;
            if (!note)  note  = &nullInt;

            // Default values of controls:
            for (auto & p: inBoolList) *p = boolDefault;
            for (auto & p: inIntList)  *p = intDefault;
            *press = -1;
            *note  = 0;

            if (!outBuffList[0] && !outBuffList[1])
                std::cout << "No output buffer declared. Output will be silent.\n";
            else {
                if (!outBuffList[0]) {
                    std::cout << "No left channel buffer declared. The right one will be used instead.\n";
                    outBuffList[0] = outBuffList[1];
                }
                if (!outBuffList[1]) {
                    std::cout << "No right channel buffer declared. The left one will be used instead.\n";
                    outBuffList[1] = outBuffList[0];
                }
                driver::Rack::outChan1 = [] (driver::Time) -> driver::Sample {
                    return *outBuffList[0];
                };
                driver::Rack::outChan2 = [] (driver::Time) -> driver::Sample {
                    return *outBuffList[1];
                };
            }
        }

    };

}
