#pragma once

#include <chrono>
#include <future>
#include <thread>
#include <tuple>
#include <utility>

namespace cynth {

    template <typename Out, typename... In>
    inline auto threadFunction (auto f) {
        return [f] (std::promise<Out> output, In &&... input) {
            if constexpr (std::same_as<Out, void>)
                f(std::forward<In>(input)...);
            else
                output.set_value(f(std::forward<In>(input)...));
        };
    }

    template <typename Out>
    struct ThreadHandle {
        std::thread      thread;
        std::future<Out> result;
    };

    template <typename Out, typename... In>
    ThreadHandle<Out> makeThread (auto f, In &&... input) {
        std::promise<Out> promise;
        std::future<Out>  future = promise.get_future();
        auto thread = std::thread{
            threadFunction<Out>(f),
            std::move(promise),
            std::forward<In>(input)...
        };
        return {std::move(thread), std::move(future)};
    }

    inline void wait (std::size_t delay) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

}
