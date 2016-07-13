#include <iostream>
#include <array>
#include <vector>
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

    // MOUVEMENTS
    std::vector<std::pair<int, int>> legal_directions(int, int) const;
    bool is_legal_move(int, int) const;
    void move(int, int);

    std::vector<std::pair<int, int>> vector_of_legal_moves() const;

    bool is_action_vector(int, int, std::pair<int, int>) const;
    void action_vector(int, int, std::pair<int, int>);

    // WIN AND EVALUATION
    bool is_finished() const;
    int8_t eval() const;
    int8_t win() const;

    private:
    bool is_legal_move_fast(int i, int j) const;
};

} // end of namespace
