#include <iostream>
#include <array>
#include <vector>
#include <utility>
#include <numeric>

#include "../include/alphabeta.hpp"

namespace Reversi {

enum Direction {N, NE, E, SE, S, SW, W, NW};

class Board {
    public:

    std::array<int8_t, 8*8> board;
    int8_t player;
    int8_t nmoves;

    Board();

    int pos(int, int) const;
    void display() const;

    // MOUVEMENTS
    std::vector<std::pair<int, int>> legal_directions(int, int) const;
    bool is_legal_move(int, int) const;
    void move(int, int);
    void move(std::pair<int, int>);

    std::vector<std::pair<int, int>> vector_of_legal_moves() const;
    std::vector<std::pair<int, int>> childs() const;

    bool is_action_vector(int, int, std::pair<int, int>) const;
    void action_vector(int, int, std::pair<int, int>);

    // WIN AND EVALUATION
    bool is_finished() const;
    int8_t score() const;
    float eval() const;
    int8_t win() const;

    std::pair<int, int> best_move(int) const;
    std::pair<int, int> best_move() const;

    private:
    bool is_legal_move_fast(int i, int j) const;
};

} // end of namespace
