#include "minmax.hpp"

#include <vector>

#ifndef USE_CILK
// Player 1 wants max, player -1 wants min
int8_t min_max(Morpion game) {
    int8_t val;
    val = game.win();
    Morpion exploration;
    // cout << " . " << (int) val << endl;
    if (val != 0) return val;
    if (game.is_tie()) return 0;

    if (game.player == 1) {
        // Looking for a maximum
        int8_t best = -1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (game.valid_move(i, j)) {
                    exploration = game;
                    exploration.move(i, j); // move changes the player's turn

                    val = min_max(exploration);

                    best = max(best, val);
                }
            }
        }
        return best;
    }
    else {
        // Looking for a minimum
        int8_t best = 1;
        // Get the min/max of all the children
        cilk_for (int i = 0; i < 3; i++) {
            cilk_for (int j = 0; j < 3; j++) {
                if (game.valid_move(i, j)) {
                    exploration = game;
                    exploration.move(i, j); // move changes the player's turn

                    val = min_max(exploration);

                    best = min(best, val);
                }
            }
        }
        return best;
    }
    return 0;
}

#else

int8_t min_max(Morpion game) {
    int8_t val;
    val = game.win();
    Morpion exploration;
    // cout << " . " << (int) val << endl;
    if (val != 0) return val;
    if (game.is_tie()) return 0;

    if (game.player == 1) {
        // Looking for a maximum
        cilk::reducer< cilk::op_max<int8_t>> best;
        cilk_for (int i = 0; i < 3; i++) {
            cilk_for (int j = 0; j < 3; j++) {
                if (game.valid_move(i, j)) {
                    exploration = game;
                    exploration.move(i, j); // move changes the player's turn

                    val = min_max(exploration);

                    best->calc_max(val);
                }
            }
        }
        return best.get_value();
    }
    else {
        // Looking for a minimum
        cilk::reducer< cilk::op_min<int8_t>> best;
        // Get the min/max of all the children
        cilk_for (int i = 0; i < 3; i++) {
            cilk_for (int j = 0; j < 3; j++) {
                if (game.valid_move(i, j)) {
                    exploration = game;
                    exploration.move(i, j); // move changes the player's turn

                    val = min_max(exploration);

                    best->calc_min(val);
                }
            }
        }
        return best.get_value();
    }
    return 0;
}

#endif

pair<int, int> Morpion::best_move() {
    vector<pair<int, int>> tie_moves;
    vector<pair<int, int>> loosing_moves;

    pair<int, int> p;
    int8_t val;
    Morpion exploration;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (valid_move(i, j)) {
                exploration = *this;
                exploration.move(i, j);
                p.first = i, p.second = j;
                val = min_max(exploration);
                if (val == player)
                    return p;
                else if (val == 0)
                    tie_moves.push_back(p);
                else
                    loosing_moves.push_back(p);
            }
        }
    }
    if (!tie_moves.empty()) return tie_moves[rand() % tie_moves.size()];
    else return loosing_moves[rand() % loosing_moves.size()];
}
