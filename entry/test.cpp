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

//using namespace cynth;
//using esl::lift;
namespace target = esl::target;
using namespace esl::sugar;

struct A {};
struct B {};

struct C {
    int foo;
    int bar;
};

constexpr auto f = ([] () {}) | ([] () {});

int main () {

    C c = {1, 2};

    auto [foo, baz] = c;

    constexpr std::variant<A, B> v = A{};
    esl::result<int> q = esl::result_error{"oops"};
    esl::result<int> r = {1};

    auto result =
        [] (int, int) -> int { return 1; } ||
        target::result{} <<=
        args(q, r);

    //static_assert(result == 1);

}
