#include <iostream>

int main () {
    int result = 0;
    int i = 0;

    while (i < 1000000) {
        result = result + 1;
        i = i + 1;
    };

    std::cout << result << '\n';
}
