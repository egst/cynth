#include "syn.hpp"
#include "sem.hpp"
#include "parser.hpp"
#include "interpreter.hpp"
#include "util.hpp"

#include <iostream>

#include "util/operations.hpp"

using namespace cynth;
using namespace yy;

template <typename T, typename U>
void handle_return (U const & value) {
    auto result = sem::get<T>(value);
    if (result)
        std::cout << "return ok: " << *result << '\n';
    else
        std::cout << "return error: " << result.error().message << '\n';
}

int main () {
    syn::node::Block syn;
    parser parse{syn};

    parse();

    std::cout << util::pretty(display(syn)) << '\n';

    sem::context ctx;

    // Built-in types:
    ctx.define_type("Bool",   {sem::type::Bool{}});
    ctx.define_type("Int",    {sem::type::Int{}});
    ctx.define_type("Float",  {sem::type::Float{}});
    ctx.define_type("String", {sem::type::String{}});

    auto result = util::unite_results(syn::evaluate(ctx)(syn));

    if (!result) {
        std::cout << "eval error:" << result.error().message << '\n';
        return 0;
    }

    auto value = *result;
    auto type  = sem::value_type(value);

    std::cout << "type:  " << display_tuple(type)  << '\n';
    std::cout << "value: " << display_tuple(value) << '\n';

}
