#include <iostream>
#include <cassert>
#include <algorithm>

#include "reversi.hpp"
#include "evaluate.hpp"
#include "search.hpp"
#include "types.hpp"

namespace Search {

/*

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

* Return a random `best move` chosen by Alpha Beta pruning.
 *
 * Input:
 *  - depth, the depth of the search
 *
 *  Output:
 *  - pair (i, j) of the best_move
 *

std::pair<int, int> best_move(Board const& pos, int depth) {
    Board exploration;
    std::pair<int, int> best;
    float best_score = 0;
    float s;

    std::vector<std::pair<int, int>> ch = pos.legal_moves();
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

*/

Move pick_move(Board pos, int depth) {
    std::vector<Move> childs = pos.legal_moves();
    assert(!childs.empty());
    Board exploration;
    Value value, bestValue, alpha, beta;
    Move best_move = childs[rand() % childs.size()];

    bestValue = -VALUE_INFINITE;
    alpha = -VALUE_INFINITE;
    beta = VALUE_INFINITE;

    for (auto &m : childs) {
        exploration = pos;
        exploration.do_move(m);
        value = search(exploration, depth, alpha, beta);
        if (value > bestValue) {
            bestValue = value;
            best_move = m;
            }
        }
        return best_move;
}

Move pick_move(Board pos) {
    return pick_move(pos, 5);
}

Value search(Board &pos, int depth, Value alpha, Value beta) {
    // Color us = pos.side_to_move();
    Value value, bestValue = -VALUE_INFINITE;
    std::vector<std::pair<int8_t, int8_t>> dirs;
    //  We reached maximal depth or the game is over
    if (depth < 0 or pos.end_game())
        return ((pos.side_to_move() == BLACK) ? 1 : -1) * Eval::evaluate_position(pos);

    for (auto &m : pos.legal_moves()) {
        // Make fun
        pos.do_move(m);
        value = -search(pos, depth-1, -beta, -alpha);
        pos.undo_move(m);
        bestValue = std::max(bestValue, value);
        alpha = std::max(alpha, value);
        if (alpha >= beta)
            break;

        //Undo move
        // std::cout << "pow" << std::endl;
    }

    return bestValue;
}

} // end of namespace Search
