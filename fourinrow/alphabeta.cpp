/* ALPHA BETA */
#include "alphabeta.hpp"
#include "fourinrow.hpp"

template <class C, typename T>
T alpha_beta(C game, int depth, T alpha, T beta) {
    T val, best;
    // Terminal case
    if (depth == 0) return game.eval();
    val = game.win();
    if (val != 0) {return val;}
    else {if (game.is_tie()) return 0;}

    // Exploration
    C exploration;

    if (game.player == 1) {
        best = -1;
        for (int i = 0; i < 7; i++) {
            if (game.valid_move(i)) {
                exploration = game;
                exploration.move(i);

                val = alpha_beta(exploration, depth-1, alpha, beta);
                best = std::max(best, val);
                if (best >= beta) {// Coupure béta
                    best =  beta;
                    break;
                }
                alpha = std::max(alpha, best);
            }
        }
    }
    else { // player -1
        best = 1;
        for (int i = 0; i < 7; i++) {
            if (game.valid_move(i)) {
                exploration = game;
                exploration.move(i);

                val = alpha_beta(exploration, depth-1, alpha, beta);
                best = std::min(best, val);
                if (best <= alpha) { // Coupure béta
                    best = alpha;
                    break;
                }
            }
            beta = std::min(beta, best);

        }
    }
    return best;
}

std::map<int8_t, std::vector<int> > FourInRow::score_moves(int depth) {
    std::map<int8_t, std::vector<int> > score;
    for (int i = 0; i < 7; i++) {
        if (valid_move(i)) {
            FourInRow exploration = *this;
            exploration.move(i);
            int8_t res = alpha_beta(exploration, depth, -1, 1);
            score[res].push_back(i);
        }
    }
    return score;
}

/* Return random best move
 *
 * Map: ordered (with std::less), biggest key is pointed by rbegin()
 */
int8_t FourInRow::ab_move(int depth) {
    std::vector<int> v;
    std::map<int8_t, std::vector<int>> score = score_moves(depth);
    if (player == 1) {
        v = score.rbegin()->second;
    }
    else {
        v = (--score.rend())->second;
    }
    return v[rand()%(v.size())];
}

// By default, depth = 10
int8_t FourInRow::ab_move() {
    return ab_move(10);
}
