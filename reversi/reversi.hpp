#ifndef _REVERSI_H
#define _REVERSI_H

#include <array>
#include <vector>
#include <utility>
#include <numeric>

#include "types.hpp"

class Board {
    public:

    Board();

    void display() const;

    // State of the board
    Color piece(int) const;
    Color piece(int, int) const;

    Color side_to_move() const;

    // Set pieces
    void set_piece(int, int, Color);
    void set_piece(std::pair<int, int>, Color);

    // Mouvements
    void move(int, int);
    void move(std::pair<int, int>);

    std::vector<std::pair<int, int>> legal_moves() const;
    std::vector<std::pair<int, int>> legal_moves(Color player) const;

    bool is_legal_move(int, int) const;
    bool is_legal_move(int i, int j, Color player) const;

    std::vector<std::pair<int, int>> childs() const;

    // Win
    bool end_game() const;
    int8_t score() const;

    // Search
    float eval() const;
    Color win() const;

    std::pair<int, int> best_move(int) const;
    std::pair<int, int> best_move() const;

    private:
    // Data member
    std::array<Color, 8*8> board;
    Color sideToMove;
    int8_t nbr_pieces;

    // Mouvement
    bool is_legal_direction(int i, int j, std::pair<int, int> v, Color player) const;
    bool is_legal_direction(int, int, std::pair<int, int>) const;
    std::vector<std::pair<int, int>> legal_directions(int, int) const;
    void flip_direction(int, int, std::pair<int, int>);
};

inline Color Board::piece(int i) const {
    return board[i];
}

inline Color Board::piece(int i, int j) const {
    return board[8*i + j];
}

inline Color Board::side_to_move() const {
    return sideToMove;
}

#endif
