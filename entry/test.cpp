#include <iostream>

//#include "config.hpp"
//#include "lift2.hpp"

//using namespace cynth;

//#define INSPECT(val) util::inspect<decltype(val)>{};
//#define INSPECT_TYPE(type) util::inspect<type>{};

namespace Detail::General {

    template <typename, typename>
    struct SameTemplate: std::false_type {};

    template <template <typename...> typename T, typename... Ts, typename... Us>
    struct SameTemplate<T<Ts...>, T<Us...>>: std::true_type {};

}

template <typename T, typename U>
concept sameTemplate = Detail::General::SameTemplate<std::remove_cvref_t<T>, std::remove_cvref_t<U>>::value;

#include <vector>
#include <optional>
#include <variant>

static_assert(sameTemplate<std::vector<int>,         std::vector<void>>);
static_assert(sameTemplate<std::optional<int>,       std::optional<void>>);
static_assert(sameTemplate<std::variant<int, float>, std::variant<>>);


int main () {

    auto s = std::size_t(0);
    auto z = std::size_t{0};

}
