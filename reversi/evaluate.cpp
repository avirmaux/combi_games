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

    int evaluate_position(const Board& board) {
        Color us = board.side_to_move();
        int sum = 0;
        if (board.end_game()) return board.win();

        for (int i = 0; i < 8*8; i++)
            sum += static_evaluation_table[i] * ((board.piece(i) == us)? 1 : -1);
        return (board.side_to_move() == WHITE)? sum : -sum;
    }

} // end of namespace Eval
