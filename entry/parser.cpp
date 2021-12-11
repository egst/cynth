#include "syn.hpp"
#include "parser.hpp"

#include "util.hpp"
#include <iostream>

using namespace cynth;
using namespace cynth::syn;
using namespace yy;

int main () {
    node::Block syn{{}};
    parser parse{syn};
    parse();
    std::cout << util::pretty(display(syn)) << '\n';
}
