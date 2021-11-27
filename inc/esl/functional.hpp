#pragma once

#include <utility>

namespace esl {

    /** Overload set from lambda functions. */
    template <typename... Fs> struct overload_type: Fs... {
        using Fs::operator()...;
    };
    template <typename... Fs> overload_type(Fs...) -> overload_type<Fs...>;

    template <typename... Fs>
    constexpr auto overload (Fs &&... fs) {
        return overload_type{std::forward<Fs>(fs)...};
    }

    template <typename... Fs>
    using overloaded = decltype(esl::overload(std::declval<Fs>()...));

}
