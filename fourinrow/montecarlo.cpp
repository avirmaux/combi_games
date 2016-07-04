#include "fourinrow.hpp"

int8_t FourInRow::random_game() {
    int8_t res;
    std::vector<int> legal_moves = vector_of_moves();
    res = win();
    if (res != 0) {return res;}
    else if (nmoves == 42) {return 0;}

    move(legal_moves[rand() % legal_moves.size()]);
    return random_game();
}

int8_t FourInRow::mc_move(int nbr_simulations) {
    std::map<int, int> stats;
    std::vector<int> legal_moves = vector_of_moves();
    FourInRow exploration;
    for (auto i : legal_moves) {
        for (int count = 0; count < nbr_simulations; count++) {
            exploration = *this;
            exploration.move(i);
            stats[i] += exploration.random_game();
        }
    }

    int best_value = stats.begin()->second, best_key = stats.begin()->first;
    if (player == 1) {
        // Looking for the key of a max value
        for (auto p : stats) {
            if (best_value < p.second) {
                best_value = p.second;
                best_key = p.first;
            }
        }
    } else {
        // Looking for the key of a min value
        for (auto p : stats) {
            if (best_value > p.second) {
                best_value = p.second;
                best_key = p.first;
            }
        }
    }
        return best_key;
}
