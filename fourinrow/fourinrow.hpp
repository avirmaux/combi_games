#ifndef _PUISSANCE_H
#define _PUISSANCE_H

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <map>
#include <vector>


class FourInRow {
    public:
    int8_t board[42]; //7 x 6
    int8_t player;
    uint8_t nmoves;

    FourInRow();
    int8_t pos(int, int);
    void display(void);

    bool valid_move(int);
    std::vector<int> vector_of_moves();
    bool move(int);

    float eval_mc(int simulations);
    float eval();

    int8_t is_tie();
    int8_t win();


    // Alpha-Beta
    int8_t ab_move(int);
    int8_t ab_move();

    // MonteCarlo
    int8_t mc_move(int simulations);

    private:
    int8_t random_game();

    int8_t win_row(int);
    int8_t win_column(int);
    int8_t win_rows();
    int8_t win_columns();
    int8_t win_diag_right_from(int, int);
    int8_t win_diag_left_from(int, int);
    int8_t win_diags();

    // Alpha-Beta
    std::map<int8_t, std::vector<int>> score_moves(int);
};

#endif
