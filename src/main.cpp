#include "ast.hpp"
#include "parser.hpp"

#include "util.hpp"
#include <iostream>

using namespace cynth;
using namespace cynth::ast;
using namespace yy;

int main () {
    node::Block ast;
    parser parse{ast};
    parse();
    std::cout << display(ast);
    /*for (auto const & item : reg::r<category::Statement>.container)
        std::cout << display(item) << '\n';*/
}
