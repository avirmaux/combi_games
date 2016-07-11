#ifndef _TAQUIN_H
#define _TAQUIN_H

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <utility>

enum Direction {UP, RIGHT, BOTTOM, LEFT};

namespace Taquin
{

template <int size_board>
class Board {
    public:

    int board[size_board * size_board];
    int empty_cell;

    Board() : empty_cell (size_board * size_board - 1) {
        for (int i = 0; i < size_board * size_board - 1; i++)
            board[i] = i+1;
        board[size_board * size_board - 1] = 0;
    }

    friend bool operator==(const Board<size_board>& lhs, const Board<size_board>& rhs) {
        for (int i = 0; i < size_board * size_board; i++)
            if (lhs.board[i] != rhs.board[i]) return false;
        return true;
    }

    friend bool operator!=(const Board<size_board>& lhs, const Board<size_board>& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const Board<size_board>& lhs, const Board<size_board>& rhs) {
        int i = 0;
        while (lhs.board[i] == rhs.board[i] and i < size_board * size_board) i++;
        return lhs.board[i] < rhs.board[i];
    }

    int pos(int i, int j) const {
        return i * size_board + j;
    }

    std::pair<int, int> reverse_pos(int i) const {
        std::pair<int, int> p;
        p.first = i / size_board;
        p.second = i % size_board;
        return p;
    }


    // MOVE UP
    bool is_move_up_valid() const {
        return (empty_cell < size_board * (size_board - 1));
    }

    void move_up() {
        std::pair<int, int> p;
        if (is_move_up_valid()) {
            p = reverse_pos(empty_cell);
            empty_cell = pos(p.first + 1, p.second);
            board[pos(p.first, p.second)] = board[empty_cell];
            board[empty_cell] = 0;
        }
    }

    // MOVE BOTTOM
    bool is_move_bottom_valid() const {
        return (empty_cell >= size_board);
    }

    void move_bottom() {
        std::pair<int, int> p;
        if (is_move_bottom_valid()) {
            p = reverse_pos(empty_cell);
            empty_cell = pos(p.first - 1, p.second);
            board[pos(p.first, p.second)] = board[empty_cell];
            board[empty_cell] = 0;
        }
    }

    // MOVE RIGHT
    bool is_move_right_valid() const {
        return (empty_cell % size_board != 0);
    }

    void move_right() {
        std::pair<int, int> p;
        if (is_move_right_valid()) {
            p = reverse_pos(empty_cell);
            empty_cell = pos(p.first, p.second - 1);
            board[pos(p.first, p.second)] = board[empty_cell];
            board[empty_cell] = 0;
        }
    }

    //MOVE LEFT
    bool is_move_left_valid() const {
        return (empty_cell % size_board != size_board - 1);
    }

    void move_left() {
        std::pair<int, int> p;
        if (is_move_left_valid()) {
            p = reverse_pos(empty_cell);
            empty_cell = pos(p.first, p.second + 1);
            board[pos(p.first, p.second)] = board[empty_cell];
            board[empty_cell] = 0;
        }
    }

    bool is_move_possible(Direction d) const {
        switch(d) {
            case UP:
                return is_move_up_valid();
            case RIGHT:
                return is_move_right_valid();
            case BOTTOM:
                return is_move_bottom_valid();
            case LEFT:
                return is_move_left_valid();
            default:
                return false;
        }
    }

    // Move general
    void move(Direction d) {
        switch(d) {
            case UP:
                return move_up();
            case RIGHT:
                return move_right();
            case BOTTOM:
                return move_bottom();
            case LEFT:
                return move_left();
        }
    }

    // PRINT
    void display() const {
        for (int i = 0; i < size_board; i++) {
            for (int j = 0; j < size_board; j++) {
                if (board[pos(i, j)] != 0)
                    std::cout << board[pos(i, j)] << " ";
                else
                    std::cout << "x ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<Direction> vector_of_valid_moves() const {
        std::vector<Direction> res;
        for (int d = UP; d <= LEFT; d++)
            if (is_move_possible(static_cast<Direction>(d)))
                res.push_back(static_cast<Direction>(d));
        return res;
    }

    std::vector<Board<size_board>> successors () const {
        std::vector<Board<size_board>> res;
        Board<size_board> b;
        for (auto d : vector_of_valid_moves()) {
            b = *this;
            b.move(d);
            res.push_back(b);
        }
        return res;
    }

    void shuffle(int nbr) {
        std::vector<Direction> v;
        for (int i = 0; i < nbr; i++) {
            v = vector_of_valid_moves();
            move(v[rand() % v.size()]);
        }
    }

    // Return the number of misplaced tiles
    int distance() const {
        int cpt = 0;
        for (int i = 0; i < size_board * size_board; i++)
            cpt += (board[i] == i+1);
        return size_board * size_board - cpt - 1;
    }

    bool is_solved() const {
        return (distance() == 0);
    }

};

} // end of namespace
#endif
