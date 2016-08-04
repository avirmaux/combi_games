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
    std::vector<std::pair<int8_t, int8_t>> make_move(Move m);
    std::vector<std::pair<int8_t, int8_t>> make_move(int, int);
    std::vector<std::pair<int8_t, int8_t>> make_move(std::pair<int, int>);

    void undo_move(Move m, std::vector<std::pair<int8_t, int8_t>>);
    void undo_move(int, int, std::vector<std::pair<int8_t, int8_t>>);
    void undo_move(std::pair<int, int>, std::vector<std::pair<int8_t, int8_t>>);


    // List of mouvements
    std::vector<Move> legal_moves() const;
    std::vector<Move> legal_moves(Color player) const;

    // 2D
    bool is_legal_move(int, int) const;
    bool is_legal_move(int i, int j, Color player) const;
    // 1D
    bool is_legal_move(Move i, Color player) const;
    bool is_legal_move(Move i) const;

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

    // Mouvement

    bool is_legal_direction(int i, int j, std::pair<int8_t, int8_t> v, Color player) const;
    bool is_legal_direction(int, int, std::pair<int8_t, int8_t>) const;
    std::vector<std::pair<int8_t, int8_t>> legal_directions(int, int) const;
    void flip_direction(int, int, std::pair<int8_t, int8_t>);
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
