#include <iostream>
#include <utility>

#include "types.hpp"


/* to_pair
 *
 * Translate a Direction to a vector, <x component, y component>
 *
 * For exemple South East is {1, -1}
 */

std::pair<int8_t, int8_t> to_pair(Direction d) {
    switch(d) {
        case(N):
            return {0, 1};
        case(NE):
            return {1, 1};
        case(E):
            return {1, 0};
        case(SE):
            return {1, -1};
        case(S):
            return {0, -1};
        case(SW):
            return {-1, -1};
        case(W):
            return {-1, 0};
        case(NW):
            return {-1, 1};
        default:
            std::cerr << "Wrong direction" << std::endl;
            return {0, 0};
    }
}
