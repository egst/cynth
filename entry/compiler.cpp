#include <iostream>
#include <tuple>

#include "esl/string.hpp"
//#include "esl/lift.hpp"
//#include "esl/sugar.hpp"

#include "context/all.hpp"
#include "interface/all.hpp"
#include "sem/all.hpp"
#include "syn/all.hpp"
#include "parser.hpp"

// TMP
#include "debug.hpp"

int main () {

    constexpr bool debug = false;

    using namespace cynth;
    //using namespace esl::sugar;
    //namespace target = esl::target;

    syn::node::Block root;

    // TODO: Use a dedicated struct as the parser argument.
    bool parseSuccess = false;
    yy::parser parse{std::pair<cynth::syn::node::Block &, bool &>{root, parseSuccess}};
    parse();

    if (!parseSuccess) return 1;

    auto recreated = esl::pretty(interface::display(root));

    if constexpr (debug)
        std::cout << "recreated input:\n" << recreated << "\n\n";

    context::Global    globalCtx;
    context::Function  functionCtx;
    context::Branching branchingCtx;
    context::Main ctx = {globalCtx, functionCtx, branchingCtx};

    // Built-in types:
    ctx.lookup.insertType("Bool",   {sem::type::Bool{}});
    ctx.lookup.insertType("Int",    {sem::type::Int{}});
    ctx.lookup.insertType("Float",  {sem::type::Float{}});
    ctx.lookup.insertType("String", {sem::type::String{}});

    // Built-in operations:
    ctx.global.insertFunction(sem::runtime::definition::floor());
    ctx.global.insertFunction(sem::runtime::definition::idiv());
    ctx.global.insertFunction(sem::runtime::definition::imod());
    ctx.global.insertFunction(sem::runtime::definition::fmod());

    // Internal library dependencies:
    ctx.global.insertInclude(c::inclusion("<math.h>"));
    ctx.global.insertInclude(c::inclusion("<stddef.h>"));
    ctx.global.insertInclude(c::inclusion("<stdbool.h>"));
    ctx.global.insertInclude(c::inclusion("<stdio.h>"));
    ctx.global.insertInclude(c::inclusion("<string.h>"));

    // Internal type definitions:
    ctx.global.insertType(c::statement(c::emptyTypeDefinition()));

    auto result = root.processProgram(ctx);

    if (!result) {
        std::cerr << "compilation error:" << result.error().message << '\n';
        return 1;
    }

    auto processed = *result;

    auto generated = ctx.assemble();

    if constexpr (debug)
        std::cout << "generated program:\n";

    std::cout << generated << '\n';

    return 0;

}
