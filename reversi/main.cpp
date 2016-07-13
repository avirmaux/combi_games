#include <iostream>

#include "reversi.hpp"

void human_vs_human() {
    Reversi::Board rev;
    int i, j;
    while(true) {
        rev.display();
        std::cout << std::endl;
        std::cin >> i >> j;
        rev.move(i, j);
    }
}



int main() {
    Reversi::Board rev;
    // rev.display();
    human_vs_human();

    return 0;
}
