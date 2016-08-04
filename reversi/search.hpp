#ifndef _SEARCH_H
#define _SEARCH_H

namespace Search {

    struct Stack {
        Move *mv;
        int ply;
        int eval;
    };

template <typename T>
T alpha_beta(Board, int, T, T);

std::pair<int, int> best_move(Board const&);
std::pair<int, int> best_move(Board const&, int);

int search(Board &pos, int depth, Value alpha, Value beta);

} // end of namespace Search


#endif
