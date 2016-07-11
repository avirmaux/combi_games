#include <iostream>
#include <array>
#include <utility>

namespace Reversi {

enum Direction {N, NE, E, SE, S, SW, W, NW};

class Board {
    public:

    std::array<int8_t, 8*8> board;
    int8_t player;

    Board();

    int pos(int, int) const;
    void display() const;

    int8_t score();

    // MOUVEMENTS
    bool is_legal_move(int i, int j) const;
    void move(int i, int j);

    bool is_action_vector(int i, int j, std::pair<int, int>) const;
    void action_vector(int i, int j, std::pair<int, int> v);
};

} // end of namespace
