#include "syn/all.hpp"
#include "esl/debug.hpp"

int main () {
    auto node = cynth::syn::node::Int{0};
    auto expr = cynth::syn::category::Expression{node};
    auto elem = cynth::syn::category::ArrayElement{node};
    elem = std::move(expr);
}
