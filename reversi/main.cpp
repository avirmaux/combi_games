#include <iostream>
#include <cstdlib>

#include "reversi.hpp"

int human_vs_human() {
    Reversi::Board rev;
    int i, j;
    while(!rev.is_finished()) {
        rev.display();
        std::cout << std::endl;
        std::cin >> i >> j;
        rev.move(i, j);
    }
    rev.display();
    return rev.eval();
}

int cpu_vs_human() {
    Reversi::Board rev;
    int i, j;
    while(!rev.is_finished()) {
        rev.display();
        std::cout << std::endl;
        if (rev.player == -1) {
            std::cin >> i >> j;
            rev.move(i, j);
        } else {
            rev.move(rev.best_move());
        }
    }
    rev.display();
    return rev.eval();
}

int cpu_vs_cpu() {
    Reversi::Board rev;
    while(!rev.is_finished()) {
        rev.display();
        std::cout << std::endl;
        if (rev.player == 1) {
            rev.move(rev.best_move(7));
        } else {
            rev.move(rev.best_move(5));
        }
    }
    rev.display();
    std::cout << std::endl;
    return rev.score();
}

int main() {
    srand(time(NULL));
    // Reversi::Board rev;
    // rev.display();
    // human_vs_human();
    // cpu_vs_human();

    // Average win
    // int avg = 0;
    // for (int i = 0; i < 10; i++) {
    //     std::cout << i << std::endl;
    //     avg += cpu_vs_cpu();
    // }
    // std::cout << "--" << std::endl;
    // std::cout << avg / 10 << std::endl;
    //
    std::cout << cpu_vs_cpu() << std::endl;

    return 0;
}
