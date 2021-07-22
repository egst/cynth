#include "ast.hpp"
#include "asg.hpp"
#include "context.hpp"
#include "parser.hpp"
#include "interpreter.hpp"
#include "util.hpp"

#include <iostream>

#include "util/operations.hpp"

using namespace cynth;
using namespace yy;

template <typename T, typename U>
void handle_return (U const & value) {
    auto result = asg::get<T>(value);
    if (result)
        std::cout << "return ok: " << *result << '\n';
    else
        std::cout << "return error: " << result.error().message << '\n';
}

int main () {
    ast::node::Block ast;
    parser parse{ast};

    parse();

    std::cout << util::pretty(ast::display(ast)) << '\n';

    context ctx;

    // Built-in types:
    ctx.define_type("Bool",   {asg::type::Bool{}});
    ctx.define_type("Int",    {asg::type::Int{}});
    ctx.define_type("Float",  {asg::type::Float{}});
    ctx.define_type("String", {asg::type::String{}});

    auto result = util::unite_results(ast::evaluate(ctx)(ast));

    if (!result) {
        std::cout << "eval error:" << result.error().message << '\n';
        return 0;
    }

    auto value = *result;
    auto type  = asg::value_type(value);

    std::cout << "type:  " << asg::display_tuple(type)  << '\n';
    std::cout << "value: " << asg::display_tuple(value) << '\n';

}
