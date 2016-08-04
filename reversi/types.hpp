#ifndef _TYPES_H
#define _TYPES_H

#include <bistset>
#include <cstdint>

enum Direction : uint8_t {N, NE, E, SE, S, SW, W, NW, DIRECTION_NB = 8};

enum Color {BLACK, WHITE, EMPTY, COLOR_NB = 3};

// A move has 2 attributes:
// to: index in the board array of the new token
// from: bitset with the directions of flips
struct Move {
    uint8_t to;
    std::bitset<8> from;
}

typedef uint8_t Move;

enum Value : int {
    SCORE_ZERO     = 0,
    VALUE_INFINITE = 50000
};

// Misc
std::pair<int8_t, int8_t> to_pair(Direction);

// Inspired from StockFish source

#define ENABLE_BASE_OPERATORS_ON(T)                             \
inline T operator+(T d1, T d2) { return T(int(d1) + int(d2)); } \
inline T operator-(T d1, T d2) { return T(int(d1) - int(d2)); } \
inline T operator*(int i, T d) { return T(i * int(d)); }        \
inline T operator*(T d, int i) { return T(int(d) * i); }        \
inline T operator-(T d) { return T(-int(d)); }                  \
inline T& operator+=(T& d1, T d2) { return d1 = d1 + d2; }      \
inline T& operator-=(T& d1, T d2) { return d1 = d1 - d2; }      \
inline T& operator*=(T& d, int i) { return d = T(int(d) * i); }

#define ENABLE_FULL_OPERATORS_ON(T)                             \
ENABLE_BASE_OPERATORS_ON(T)                                     \
inline T& operator++(T& d) { return d = T(int(d) + 1); }        \
inline T& operator--(T& d) { return d = T(int(d) - 1); }        \
inline T operator/(T d, int i) { return T(int(d) / i); }        \
inline int operator/(T d1, T d2) { return int(d1) / int(d2); }  \
inline T& operator/=(T& d, int i) { return d = T(int(d) / i); }

ENABLE_FULL_OPERATORS_ON(Value)
ENABLE_FULL_OPERATORS_ON(Direction)

inline Value operator+(Value v, int i) { return Value(int(v) + i); }
inline Value operator-(Value v, int i) { return Value(int(v) - i); }
inline Value& operator+=(Value& v, int i) { return v = v + i; }
inline Value& operator-=(Value& v, int i) { return v = v - i; }


#endif
