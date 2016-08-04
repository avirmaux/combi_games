#ifndef _SEARCH_H
#define _SEARCH_H

#include "types.hpp"

namespace Search {

struct RootMove {
    Move m;
    Value score= -VALUE_INFINITE;

    bool operator<(const RootMove& mv) const {return mv.score < score; }
};

typedef std::vector<RootMove> RootMoves;

struct Stack {
    Move *pv;
    int ply;
    int eval;
};

template <typename T>
T alpha_beta(Board, int, T, T);

std::pair<int, int> best_move(Board const&);
std::pair<int, int> best_move(Board const&, int);

Move pick_move(Board , int);
Move pick_move(Board);
Value search(Board&, int, Value, Value);

} // end of namespace Search


#endif
