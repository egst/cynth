#include "ast.hpp"

#include <iostream>

using namespace cynth;

int main () {
    ast::node::If node {
        .condition = ast::category::Expression {
            ast::node::Int{1}
        },
        .positive_branch = ast::category::Statement {
            ast::node::Int{2}
        },
        /*.negative_branch = ast::category::Statement {
            ast::node::Int{3}
        }*/
    };

    //ast::node::Int node{1};
    //ast::node::optional_component comp{ast::node::Int{1}};
    //ast::node::optional_component comp{ast::category::Expression{ast::node::Int{1}}};

    std::cout << ast::display(node) << '\n';
}
