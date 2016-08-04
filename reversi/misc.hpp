#ifndef _MISC_H
#define _MISC_H

std::pair<int8_t, int8_t> to_pair(Direction);

// Set ith bit to 1
inline void set_bit(int8_t x, int8_t i) {
    x |= 1 << i;
}

inline void clear_bit(int8_t x, int8_t i) {
    x &= ~(1 << i);
}

inline bool is_set(int8_t x, int8_t i) {
    return (x >> i) & 1;
}
#endif
