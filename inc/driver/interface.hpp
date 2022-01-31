#pragma once

#include <atomic>
#include <concepts>
#include <string>

#undef interface

namespace cynth::driver {

    // TODO: Take these from a central config.
    using Time   = int;
    using Sample = float;

    using Signal    = Sample (*) (Time);
    using Evaluator = void   (*) (Time); // Note: Maybe I'll need some output status in the future.

    namespace interface {

        template <typename T>
        concept controller = requires (typename T::Status status) {
            T::Status::ok;
            T::Status::error;
            { T::message(status) } -> std::same_as<std::string>;
            { T::init()          } -> std::same_as<typename T::Status>;
            { T::initialized()   } -> std::same_as<bool>;
            { T::start()         } -> std::same_as<typename T::Status>;
            { T::stop()          } -> std::same_as<void>;
            { T::sampleRate()    } -> std::same_as<double>;
        };

    }

    struct Rack {

        inline static std::atomic<int> offset = 0;

        // This function will be evaluated before every write.
        inline static Evaluator eval = [] (Time) {};

        // These functions will be evaluated on every write for every channel.
        // Their output values are used as the samples to be written.
        inline static Signal outChan1 = [] (Time) -> Sample { return 0; };
        inline static Signal outChan2 = [] (Time) -> Sample { return 0; };

    };

}
