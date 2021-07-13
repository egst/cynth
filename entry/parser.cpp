#include "ast.hpp"
#include "parser.hpp"

#include "util.hpp"
#include <iostream>

using namespace cynth;
using namespace cynth::ast;
using namespace yy;

int main () {
    node::Block ast{{}};
    parser parse{ast};
    parse();
    std::cout << util::pretty(display(ast)) << '\n';
}
