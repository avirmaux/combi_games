#ifndef _MORPION_H
#define _MORPION_H

#include <iostream>
#include <cstring>
#include <cstdint>
#include <utility>

class Morpion {
    public:
    int8_t board[9];
    int8_t player; // -1 or 1
    uint8_t nmoves;

    Morpion();

    void display();
    int8_t win();
    int8_t eval();
    int8_t pos(int, int);

    bool valid_move(int, int);
    bool move(int, int);
    bool is_tie();

    std::pair<int, int> best_move();
};

#endif
