#include <iostream>
#include <cstdlib>

#include "fourinrow.hpp"

int CPU_move_ab(FourInRow game, int depth) {
    return game.ab_move(depth);
}

int CPU_move_ab(FourInRow game) {
    return game.ab_move();
}

int CPU_move_mc(FourInRow game, int simulations) {
    return game.mc_move(simulations);
}
int CPU_move_mc(FourInRow game) {
    return game.mc_move(2000);
}

void human_vs_CPU() {
    int i;
    FourInRow game;
    game.player = 1;
    while (game.nmoves < 42 and game.win() == 0) {
        if (game.player == 1) {
            std::cin >> i;
            game.move(i);
        }
        else {
            game.move(CPU_move_mc(game, 10000));
            // game.move(CPU_move_ab(game));
        }
        game.display();
        std::cout << std::endl;
    }
    if (game.win() != 0) {
        std::cout << "Player " << (int) game.win() << " won" << std::endl;
    }
    else {
        std::cout << "Tie" << std::endl;
    }
}

int ab_vs_mc(void) {
    FourInRow game;
    game.player = 1; // AlphaBeta begins
    while (game.nmoves < 42 and game.win() == 0) {
        if (game.player == 1) {
            game.move(CPU_move_ab(game));
            // game.move(CPU_move_mc(game, 3000));
        }
        else {
            game.move(CPU_move_mc(game, 6000));
        }
        game.display();
        std::cout << std::endl;
    }
    return game.win();
}

void meta_ab_vs_mc(void) {
    int x;
    std::vector<int> res(3, 0);
    for (int i = 0; i < 30; i++) {
        x = ab_vs_mc();
        std::cout << "Game: " << i << " -- Winner: " << x << std::endl;
        res[x + 1] ++;
    }

    std::cout << res[0] << " :: " << res[1] << " :: " << res[2] << std::endl;
}

int main() {
    srand(time(NULL));

    // FourInRow game;
    // game.best_move(12);
    // exit(0);

    human_vs_CPU();
    //
    // std::cout << (int) ab_vs_mc() << std::endl;

    // Alpha Beta vs Monte Carlo
    // meta_ab_vs_mc();
    return 0;
}
