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

    auto result = util::single(ast::evaluate(ctx)(ast));

    if (!result) {
        std::cout << "eval error:" << result.error().message << '\n';
        return 0;
    }

    std::cout << "eval ok\n";

    auto value = *result;
    /*
    std::cout << "return type: ";
    std::visit (
        util::overload {
            [] (asg::value::Bool const & val) {
                std::cout << "Bool\n";
                handle_return<bool>(val);
            },
            [] (asg::value::Int const & val) {
                std::cout << "Int\n";
                handle_return<integral>(val);
            },
            [] (asg::value::Float const & val) {
                std::cout << "Float\n";
                handle_return<floating>(val);
            },
            [] (asg::value::In const &) {
                std::cout << "T in\n";
            },
            [] (asg::value::Out const &) {
                std::cout << "T out\n";
            },
            [] (asg::value::Const const &) {
                std::cout << "T const\n";
            },
            [] (asg::value::Array const & val) {
                std::cout << "T [n]\n";
            },
            [] (asg::value::Buffer const &) {
                std::cout << "buffer [n]\n";
            },
            [] (asg::value::Function const &) {
                std::cout << "T (U)\n";
            },
            [] (auto const &) {
                std::cout << "?";
            }
        },
        value.value
    );
    */

    //return 0;

    // TODO: make this work
    std::cout << asg::display(value) << '\n';

}
