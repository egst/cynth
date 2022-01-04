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

    using namespace cynth;
    //using namespace esl::sugar;
    //namespace target = esl::target;

    syn::node::Block root;

    yy::parser parse{root};
    parse();

    auto recreated = esl::pretty(interface::display(root));

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

    auto result = root.processProgram(ctx);

    if (!result) {
        std::cout << "compilation error:" << result.error().message << '\n';
        return 1;
    }

    auto processed = *result;

    auto generated = ctx.assemble();

    std::cout << "generated program:\n" << generated << '\n';

    return 0;

}
