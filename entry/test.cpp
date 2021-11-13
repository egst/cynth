#include <iostream>

#include "config.hpp"
#include "lift2.hpp"


using namespace cynth;

int main () {
    /*
    int result = 0;
    int i = 0;

    while (i < 1000000) {
        result = result + 1;
        i = i + 1;
    };

    std::cout << result << '\n';
    */

    // TODO: just `variant` doesn't work.
    constexpr auto f = lift<target::variant>(
        [] (int   val) -> int { return 1; }//,
        //[] (float val) -> int { return 2; }
    );

    constexpr variant<int, float> v = 2.5f;

    constexpr auto r = f(v);

    constexpr auto u = std::visit([] (int val) -> int { return 1; }, v);

    //static_assert(r == 2);

}
