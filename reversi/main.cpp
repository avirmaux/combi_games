#include <iostream>
#include <cstdlib>

#include "reversi.hpp"
#include "search.hpp"
#include "evaluate.hpp"
#include "types.hpp"
#include "misc.hpp"

int human_vs_human() {
    Board rev;
    int i, j;
    while(!rev.end_game()) {
        rev.display();
        std::cout << "&" << std::endl;
        std::cout << "#Moves = " << rev.legal_moves().size() << std::endl;
        std::cin >> i >> j;
        rev.do_move(rev.make_move(i, j));
    }
    rev.display();
    return Eval::evaluate_position(rev);
}

/*
int cpu_vs_human() {
    Board rev;
    int i, j;
    while(!rev.end_game()) {
        rev.display();
        std::cout << std::endl;
        if (rev.side_to_move() == BLACK) {
            std::cin >> i >> j;
            rev.make_move(i, j);
        } else {
            rev.make_move(Search::best_move(rev, 9));
        }
    }
    rev.display();
    return Eval::evaluate_position(rev);
}

int cpu_vs_cpu() {
    Board rev;
    while(!rev.end_game()) {
        rev.display();
        std::cout << std::endl;
        if (rev.side_to_move() == BLACK) {
            rev.do_move(Search::pick_move(rev, 9));
        } else {
            rev.do_move(Search::pick_move(rev, 5));
        }
    }
    rev.display();
    std::cout << std::endl;
    return rev.score();
}
*/

int main() {
    srand(time(NULL));
    Board rev;
    // rev.display();
    // human_vs_human();
    rev.display();
    std::cout << human_vs_human() << std::endl;

    // std::cout << cpu_vs_cpu() << std::endl;

    // Average win
    // int avg = 0;
    // for (int i = 0; i < 10; i++) {
    //     std::cout << i << std::endl;
    //     avg += cpu_vs_cpu();
    // }
    // std::cout << "--" << std::endl;
    // std::cout << avg / 10 << std::endl;
    //
    // std::cout << cpu_vs_cpu() << std::endl;
    // std::cout << cpu_vs_human() << std::endl;

    return 0;
}
