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
    Color piece(int8_t) const;
    Color piece(int8_t, int8_t) const;

    Color side_to_move() const;

    // Set pieces
    void set_piece(int, int, Color);
    void set_piece(std::pair<int, int>, Color);

    // Mouvements

    // Return a Move struct out of coordinates, const
    Move make_move(int8_t) const;
    Move make_move(int8_t, int8_t) const;

    // Do the move, non const
    void do_move(Move m);
    void do_move(int8_t, int8_t);

    // Undo the move, non const
    void undo_move(Move m);

    // List of mouvements
    std::vector<Move> legal_moves() const;
    std::vector<Move> legal_moves(Color player) const;

    bool is_legal_move(int8_t) const;

    // Win
    bool end_game() const;
    int8_t score() const;

    // Search
    Color win() const;

    std::pair<int, int> best_move(int) const;
    std::pair<int, int> best_move() const;

    private:

    // Data member
    std::array<Color, 8*8> board;
    Color sideToMove;
    int8_t nbr_pieces;

    // Mouvements

    bool is_legal_direction(int8_t, int8_t, Direction, Color) const;
    bool is_legal_direction(int8_t, int8_t, Direction) const;
    int8_t legal_directions(int8_t) const;
    int8_t legal_directions(int8_t, int8_t) const;

    void flip_direction(int8_t, int8_t, Direction);
};

inline Color Board::piece(int8_t i) const {
    return board[i];
}

inline Color Board::piece(int8_t i, int8_t j) const {
    return board[8*i + j];
}

inline Color Board::side_to_move() const {
    return sideToMove;
}

#endif
