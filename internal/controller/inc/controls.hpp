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

    namespace detail::controls {

        template <typename T>
        std::remove_cvref_t<T> get (std::vector<T *> const & list, std::size_t n, std::remove_cvref_t<T> defval) {
            if (n >= list.size() || !list[n]) return defval;
            return *list[n];
        }

        template <typename T>
        std::remove_cvref_t<T> get (std::map<std::string, T *> const & map, std::string const & n, std::remove_cvref_t<T> defval) {
            auto it = map.find(n);
            if (it == map.end() || !it->second) return defval;
            return *it->second;
        }

        template <typename T>
        void set (std::vector<T *> & list, std::size_t n, std::remove_cvref_t<T> val, bool log = false) {
            if (n >= list.size() || !list[n]) return;
            *list[n] = val;
            if (log) std::printf("[%zu]: %s\n", n + 1, val ? "on" : "off");
            if constexpr (std::same_as<std::remove_cvref_t<T>, bool>)
                if (log) std::printf("[%zu]: %s\n", n + 1, val ? "on" : "off");
            if constexpr (std::same_as<std::remove_cvref_t<T>, Integral>)
                if (log) std::printf("[%zu]: %i\n", n + 1, static_cast<int>(val));
        }

        template <typename T>
        void set (std::map<std::string, T *> & map, std::string const & n, std::remove_cvref_t<T> val, bool log = false) {
            auto it = map.find(n);
            if (it == map.end() || !it->second) return;
            *it->second = val;
            if constexpr (std::same_as<std::remove_cvref_t<T>, bool>)
                if (log) std::printf("[%s]: %s\n", n.data(), val ? "on" : "off");
            if constexpr (std::same_as<std::remove_cvref_t<T>, Integral>)
                if (log) std::printf("[%s]: %i\n", n.data(), static_cast<int>(val));
        }

        inline void mod (std::vector<Integral *> & list, std::size_t n, Integral step, bool log = false) {
            if (n >= list.size() || !list[n]) return;
            *list[n] += step;
            if (log) std::printf("[%zu]: %i\n", n + 1, static_cast<int>(*list[n]));
        }

        inline void mod (std::map<std::string, Integral *> & map, std::string const & n, Integral step, bool log = false) {
            auto it = map.find(n);
            if (it == map.end() || !it->second) return;
            *it->second += step;
            if (log) std::printf("[%s]: %i\n", n.data(), static_cast<int>(*it->second));
        }

    }

    struct Controls {
        constexpr static bool     boolDefault = false;
        constexpr static unsigned intDefault  = 0;
        constexpr static unsigned intStep     = 1;

        static bool     getInBool (std::size_t         n) { return detail::controls::get(inBoolList,  n, boolDefault); }
        static bool     getInBool (std::string const & n) { return detail::controls::get(inBoolMap,   n, boolDefault); }
        static bool     getBool   (std::size_t         n) { return detail::controls::get(outBoolList, n, boolDefault); }
        static bool     getBool   (std::string const & n) { return detail::controls::get(outBoolMap,  n, boolDefault); }
        static Integral getInInt  (std::size_t         n) { return detail::controls::get(inIntList,   n, intDefault);  }
        static Integral getInInt  (std::string const & n) { return detail::controls::get(inIntMap,    n, intDefault);  }
        static Integral getInt    (std::size_t         n) { return detail::controls::get(outIntList,  n, intDefault);  }
        static Integral getInt    (std::string const & n) { return detail::controls::get(outIntMap,   n, intDefault);  }

        static void setBool (std::size_t         n, bool     value, bool log) { detail::controls::set(inBoolList, n, value, log); }
        static void setBool (std::string const & n, bool     value, bool log) { detail::controls::set(inBoolMap,  n, value, log); }
        static void setInt  (std::size_t         n, Integral value, bool log) { detail::controls::set(inIntList,  n, value, log); }
        static void setInt  (std::string const & n, Integral value, bool log) { detail::controls::set(inIntMap,   n, value, log); }

        static void on  (std::size_t         n, bool log = false) { setBool(n, true,  log); }
        static void on  (std::string const & n, bool log = false) { setBool(n, true,  log); }
        static void off (std::size_t         n, bool log = false) { setBool(n, false, log); }
        static void off (std::string const & n, bool log = false) { setBool(n, false, log); }

        static void upInt   (std::size_t         n, bool log = false) { return detail::controls::mod(inIntList, n,  intStep, log); }
        static void upInt   (std::string const & n, bool log = false) { return detail::controls::mod(inIntMap,  n,  intStep, log); }
        static void downInt (std::size_t         n, bool log = false) { return detail::controls::mod(inIntList, n, -intStep, log); }
        static void downInt (std::string const & n, bool log = false) { return detail::controls::mod(inIntMap,  n, -intStep, log); }

        inline static void run (Integral time) {
            auto step = time - lastStep;
            lastStep = time;
            if (press   && *press   >= 0) *press   += step;
            if (release && *release >= 0) *release += step;
            //std::cout << "step: " << *press << " : " << *release << '\n';
        }

        inline static void toneStart (std::size_t n) {
            if (press)   *press   = 0;
            if (release) *release = -1;
            if (note)    *note    = n;
        }

        inline static void toneStop (std::size_t n) {
            if (*note && n != *note) return;
            if (press) *press   = -1;
            if (press) *release = 0;
        }

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
            press   = cth_input_int("press");
            release = cth_input_int("release");
            note    = cth_input_int("note");

            constexpr auto second = [] (auto p) { return p.second; };
            std::transform(outBuffMap.begin(), outBuffMap.end(), std::back_inserter(outBuffList), second);
            std::transform(inBoolMap.begin(),  inBoolMap.end(),  std::back_inserter(inBoolList),  second);
            std::transform(inIntMap.begin(),   inIntMap.end(),   std::back_inserter(inIntList),   second);
            std::transform(outBoolMap.begin(), outBoolMap.end(), std::back_inserter(outBoolList), second);
            std::transform(outIntMap.begin(),  outIntMap.end(),  std::back_inserter(outIntList),  second);

            // Direct empty controls somewhere to avoid checking their presence before every write:
            /*
            for (auto & p: inBoolList) if (!p) p = &nullBool;
            for (auto & p: inIntList)  if (!p) p = &nullInt;
            if (!press)   press = &nullInt;
            if (!release) press = &nullInt;
            if (!note)    note  = &nullInt;
            */

            // Default values of controls:
            for (auto & p: inBoolList) if (p) *p = boolDefault;
            for (auto & p: inIntList)  if (p) *p = intDefault;
            if (press)   *press   = -1;
            if (release) *release = -1;
            if (note)    *note    = 0;

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

    protected:
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

        inline static Integral * press   = nullptr;
        inline static Integral * release = nullptr;
        inline static Integral * note    = nullptr;

        inline static std::atomic<int> lastStep = 0;

        /*
        inline static bool nullBool = false;
        inline static Integral nullInt  = 0;
        */
    };

}
