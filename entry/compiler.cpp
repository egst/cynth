#include "syn/all.hpp"
#include "parser.hpp"

int main () {

    using namespace cynth;

    syn::node::Block syn;

    yy::parser parse{syn};
    parse();

}
