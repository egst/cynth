#include "util.hpp"
#include "ast.hpp"
#include <iostream>

using namespace cynth::lang;

int main () {

    category::Any ast {
        node::Block {
            {
                new category::Statement {
                    node::Assignment {
                        new node::Name{"foo"},
                        new category::Expressible{node::Name{"bar"}}
                    }
                },
                new category::Statement {
                    node::Definition {
                        new node::Name{"foo"},
                        new category::Type {
                            node::TypeName{"Foo"}
                        },
                        new category::Expressible{node::Name{"bar"}}
                    }
                },
            }
        }
    };

    auto n1 = node::Name{"foo"};
    auto n2 = category::Expressible{node::Name{"bar"}}

    auto stmt1 = category::Statement {
        node::Assignment {&n1, &n2}
    }

    category::Any ast {
        node::Block {
            {
                stmt1,
                new category::Statement {
                    node::Definition {
                        new node::Name{"foo"},
                        new category::Type {
                            node::TypeName{"Foo"}
                        },
                        new category::Expressible{node::Name{"bar"}}
                    }
                },
            }
        }
    };

    std::cout << display(ast) << '\n';

}
