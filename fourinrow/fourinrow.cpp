#include "alphabeta.hpp"
#include "fourinrow.hpp"

FourInRow::FourInRow()
    : player(1), nmoves(0) {
        for (int i = 0; i < 42; i++)
            board[i] = 0;
}

int8_t FourInRow::pos(int i, int j) {
    return board[7*i + j];
}

void FourInRow::display() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            switch (pos(i, j)) {
                case -1:
                    std::cout << " o ";
                    break;
                case 1:
                    std::cout << " x ";
                    break;
                default:
                    std::cout << " . ";
            }
        }
        std::cout << std::endl;
    }
}

bool FourInRow::valid_move(int i) {
    return !(i < 0 or i > 6 or pos(0, i) != 0);
}

std::vector<int> FourInRow::vector_of_moves() {
    std::vector<int> res;
    for (int i = 0; i < 7; i++) {
        if (valid_move(i)) res.push_back(i);
    }
    return res;
}

/* player move
 *
 * Input:
 *  - i, row
 *
 *  Output:
 *  - true or false whether a move had been played or not
 */
bool FourInRow::move(int i) {
    int row = 0;
    if (i < 0 or i > 6 or pos(0, i) != 0) {
        std::cerr << "Forbidden move" << std::endl;
        return false;
    }
    else {
        while(row < 6 and pos(row, i) == 0) row++;
        board[7*(row-1) + i] = player;
        player = -player;
        nmoves++;
    }
    return true;
}

/* Return true if a row is a winning row
 *
 * Input:
 *  - row, a row
 */
int8_t FourInRow::win_row(int row) {
    int col = 0;
    int8_t tmp, p, cpt;
    p = 0; cpt = 0;
    while (cpt < 4 and col < 7) {
        tmp = pos(row,  col);
        if (tmp == p && p != 0) {
            cpt++;}
        else {
            cpt = 1;
            p = tmp;
        }
        col++;
    }
    if (cpt == 4) return p;
    else return 0;
}

int8_t FourInRow::win_rows() {
    int8_t p;
    for (int row = 0; row < 6; row++) {
        p = win_row(row);
        if (p != 0) return p;
    }
    return 0;
}

/* Return true if a column is a winning row
 *
 * Input:
 *  - col, a column
 */
int8_t FourInRow::win_column(int col) {
    int row = 0;
    int8_t tmp, p, cpt;
    p = 0; cpt = 0;
    while (cpt < 4 and row < 6) {
        tmp = pos(row,  col);
        if (tmp == p && p != 0) {
            cpt++;}
        else {
            cpt = 1;
            p = tmp;
        }
        row++;
    }
    if (cpt == 4) return p;
    else return 0;
}

int8_t FourInRow::win_columns() {
    int8_t p;
    for (int col = 0; col < 6; col++) {
        p = win_column(col);
        if (p != 0) return p;
    }
    return 0;
}

/* Check if
 * o o o x
 * o o x o
 * o x o o
 * x o o o
 *
 * Input:
 *  -i, j, coordinate of lower left
 */
int8_t FourInRow::win_diag_right_from(int i, int j) {
    if ((pos(i, j) != 0) and
        (pos(i, j) == pos(i-1, j+1)) and
        (pos(i, j) == pos(i-2, j+2)) and
        (pos(i, j) == pos(i-3, j+3)))
        return pos(i, j);
    else
        return 0;
}

/* Check if
 * x o o o
 * o x o o
 * o o x o
 * o o o x
 *
 * Input:
 *  -i, j, coordinate of lower right
 */
int8_t FourInRow::win_diag_left_from(int i, int j) {
    if ((pos(i, j) != 0) and
        (pos(i, j) == pos(i-1, j-1)) and
        (pos(i, j) == pos(i-2, j-2)) and
        (pos(i, j) == pos(i-3, j-3)))
        return pos(i, j);
    else
        return 0;
}

int8_t FourInRow::win_diags() {
    int8_t p;
    // Diag left
    for (int i = 3; i < 6; i++) {
        for (int j = 3; j < 7; j++) {
            p = win_diag_left_from(i, j);
            if (p != 0) return p;
        }
    }

    // Diag right
    for (int i = 3; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            p = win_diag_right_from(i, j);
            if (p != 0) return p;
        }
    }

    // Else no diagonal won
    return 0;
}

int8_t FourInRow::win() {
    int8_t p;
    p = win_rows();
    if (p != 0) return p;
    p = win_columns();
    if (p != 0) return p;
    p = win_diags();
    if (p != 0) return p;
    return 0;
}

float FourInRow::eval_mc(int nbr_simulations) {
    int stats = 0;
    std::vector<int> legal_moves = vector_of_moves();
    FourInRow exploration;
    for (int count = 0; count < nbr_simulations; count++) {
        exploration = *this;
        stats += exploration.random_game();
    }
    return (stats / nbr_simulations);
}

float FourInRow::eval() {
    // return eval_mc(10);
    return win();
}

int8_t FourInRow::is_tie() {
    return (nmoves == 42 and win() == 0);
}
