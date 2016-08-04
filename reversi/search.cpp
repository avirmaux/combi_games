#include <iostream>
#include <algorithm>

#include "reversi.hpp"
#include "evaluate.hpp"
#include "search.hpp"

namespace Search {

template <typename T>
T alpha_beta(Board pos, int depth, T alpha, T beta) {
    Board exploration;
    T val, best;

    // Terminal case
    if (depth == 0 or pos.end_game()) return Eval::evaluate_position(pos);

    // Exploration

    if (pos.side_to_move() == BLACK) {
        best = alpha;
        for (auto i : pos.childs()) {
            exploration = pos;
            exploration.make_move(i);

            val = alpha_beta(exploration, depth-1, alpha, beta);
            best = std::max(best, val);
            if (best >= beta) {// Coupure béta
                best =  beta;
                break;
            }
            alpha = std::max(alpha, best);
        }
    }

    else if (pos.side_to_move() == WHITE) {
        best = beta;
        for (auto i : pos.childs()) {
            exploration = pos;
            exploration.make_move(i);

            val = alpha_beta(exploration, depth-1, alpha, beta);
            best = std::min(best, val);
            if (best <= alpha) { // Coupure béta
                best = alpha;
                break;
            }
        }
        beta = std::min(beta, best);

    }

    else {
        std::cerr << "Error: player " << pos.side_to_move() << " unknown." << std::endl;
        exit(-1);
    }

    return best;
}

/* Return a random `best move` chosen by Alpha Beta pruning.
 *
 * Input:
 *  - depth, the depth of the search
 *
 *  Output:
 *  - pair (i, j) of the best_move
 */

std::pair<int, int> best_move(Board const& pos, int depth) {
    Board exploration;
    std::pair<int, int> best;
    float best_score = 0;
    float s;

    std::vector<std::pair<int, int>> ch = pos.childs();
    best = ch[rand()%ch.size()]; // Default is random move


    for (auto x : ch) {
        exploration = pos;
        exploration.make_move(x);
        s = alpha_beta(exploration, depth, -1, 1);
        if ((exploration.side_to_move() == BLACK  and s > best_score) or
            (exploration.side_to_move() == WHITE and s < best_score)) {
            best_score = s;
            best = x;
        }
    }
    return best;
}

std::pair<int, int> best_move(Board const& pos) {
    return best_move(pos, 5);
}


int search(Board &pos, Stack *st, int depth, Value alpha, Value beta) {
    Color us = pos.side_to_move();
    return SCORE_ZERO;
}

} // end of namespace Search
