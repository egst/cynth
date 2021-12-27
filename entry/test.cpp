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
//namespace target = esl::target;
//using namespace esl::sugar;

int main () {

    std::string s1 = R"code(
        int foo (int x) {
            return x + 1;
        }
    )code";

    std::string s2 = R"code(
        #include ""
    )code";

    return 0;

}
