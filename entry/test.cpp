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

#include "sem/all.hpp"
#include "sem/translation.hpp"

using namespace cynth;
//using esl::lift;
//namespace target = esl::target;
//using namespace esl::sugar;

template <typename T>
struct Foo {
    int bar;
    int foo (T x);
};

int main () {

    sem::FunctionDefinition f = {esl::component_vector<sem::value::Function>{}};
    using T = sem::value::Function;
    //#define I {}
    //#define I {"", sem::CompleteType{sem::type::Int{}}}
    #define I {f}
    //#define I {esl::component_vector<sem::value::Function>{}}
    T a = I;
    T b = I;
    a = b;
    a = b;

    foo;

    return 0;

}
