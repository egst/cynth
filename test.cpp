#include "ast/interface.hpp"
#include "ast/categories.hpp"

#include <iostream>

using namespace cynth;

int main () {
    //ast::node::Block ast{.statements = ast::node::component_vector<ast::category::Statement>{}};

    ast::node::Int node{1};

    ast::category::Pattern ast = node;

    std::cout << ast::display(ast) << '\n';
}
