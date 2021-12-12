#include "syn.hpp"
#include "sem.hpp"
#include "parser.hpp"
#include "interpreter.hpp"
#include "util.hpp"

#include <iostream>

#include "util/operations.hpp"

using namespace cynth;

int main () {
    syn::node::Block syn;

    yy::parser parse{syn};
    parse();

    std::cout <<
        "INPUT:\n" <<
        util::pretty(display(syn)) << '\n';

    sem::context ctx;

    // Built-in types:
    ctx.define_type("Bool",   {sem::type::Bool{}});
    ctx.define_type("Int",    {sem::type::Int{}});
    ctx.define_type("Float",  {sem::type::Float{}});
    ctx.define_type("String", {sem::type::String{}});

    auto result = util::unite_results(syn.evaluate<false>(ctx));

    if (!result) {
        std::cout << "eval error:" << result.error().message << '\n';
        return 0;
    }

    auto value = *result;
    auto type  = sem::value_type(value);

    std::cout <<
        "RETURNED:\n"
        "type:  " << display_tuple(type)  << '\n' <<
        "value: " << display_tuple(value) << '\n';

    std::cout << "CONTEXT:\n";

    // TODO
    /*for (auto && [name, val]: ctx.values)
        std::cout << display_tuple(val.value) << '\n';*/

    std::cout << "STORED:\n";

    for (auto && val: ctx.stored_values<sem::value::BufferValue>())
        std::cout << "buff..." << '\n';

    sem::translation_context tctx;
}
