#include <algorithm>

template <class C, typename T>
T alpha_beta(C game, int depth, T alpha, T beta) {
    C exploration;
    T val, best;

    // Terminal case
    if (depth == 0) return game.eval();
    if (game.is_finished()) return game.eval();

    // Exploration

    if (game.player == 1) {
        best = alpha;
        for (auto i : game.childs()) {
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

    else if (game.player == -1) {
        best = beta;
        for (auto i : game.childs()) {
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

    else {
        std::cerr << "Error: player " << game.player << " unknown." << std::endl;
        exit(-1);
    }

    return best;
}
