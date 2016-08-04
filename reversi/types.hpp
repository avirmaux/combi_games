#ifndef _TYPES_H
#define _TYPES_H

enum Direction {N, NE, E, SE, S, SW, W, NW, DIRECTION_NB = 8};

enum Color {BLACK, WHITE, EMPTY, COLOR_NB = 3};

// A move needs 6 bits to be stored
// 5 bits: positions
// last bit: white / black
typedef uint8_t Move;

enum Value : int {
    SCORE_ZERO     = 0,
    VALUE_INFINITE = 50000
};

// Misc
std::pair<int8_t, int8_t> to_pair(Direction);

#endif
