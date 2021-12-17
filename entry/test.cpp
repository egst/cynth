#include <iostream>
#include <variant>

#include "esl/concepts.hpp"
#include "esl/debug.hpp"
#include "esl/functional.hpp"
#include "esl/lift.hpp"
#include "esl/macros.hpp"
#include "esl/result.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/type_manip.hpp"
#include "esl/zip.hpp"


#include <concepts>
#include <optional>
#include <utility>

#include "esl/concepts.hpp"
#include "esl/functional.hpp"
#include "esl/ranges.hpp"
#include "esl/sugar.hpp"

#include "context/c.hpp"
#include "interface/forward.hpp"
#include "interface/types.hpp"
#include "sem/compound.hpp"
#include "sem/declarations.hpp"
#include "sem/values.hpp"

// Completing declarations:
#include "sem/types.hpp"
#include "sem/values.hpp"



//using namespace cynth;
//using esl::lift;
namespace target = esl::target;
using namespace esl::sugar;

struct A {};
struct B {};

constexpr auto f = ([] () {}) | ([] () {});

int main () {

    constexpr std::variant<A, B> value = A{};

    constexpr auto result = value >>= target::variant{} &&
        [] (A const &) -> int { return 1; } |
        [] (B const &) -> int { return 2; };

    static_assert(result == 1);

}
