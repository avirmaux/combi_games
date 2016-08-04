#include <vector>

#include "reversi.hpp"

namespace Eval {

    const std::array<int, 8*8> static_evaluation_table =
    {  5, -1, 1, 1, 1, 1, -1,  5,
        -1, -2, 1, 1, 1, 1, -2, -1,
        1,  1, 2, 2, 2, 2,  1,  1,
        1,  1, 2, 2, 2, 2,  1,  1,
        1,  1, 2, 2, 2, 2,  1,  1,
        1,  1, 2, 2, 2, 2,  1,  1,
        -1, -2, 1, 1, 1, 1, -2, -1,
        5, -1, 1, 1, 1, 1, -1,  5 };

    const int sum_evaluation_table_total =
        std::accumulate(static_evaluation_table.begin(), static_evaluation_table.end(), 0);

    Value evaluate_position(const Board& pos) {
        Color us = pos.side_to_move();
        Value sum = SCORE_ZERO;
        if (pos.end_game()) return (us == BLACK)? VALUE_INFINITE : -VALUE_INFINITE;

        for (int i = 0; i < 8*8; i++)
            sum += static_evaluation_table[i] * ((pos.piece(i) == us)? 1 : -1);
        return (pos.side_to_move() == BLACK)? sum : -sum;
    }

} // end of namespace Eval
