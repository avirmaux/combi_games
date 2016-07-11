#include "reversi.hpp"

namespace Reversi {

std::pair<int, int> to_pair(Direction d) {
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

Board::Board() : player(1) {
    board.fill(0);

    board[pos(3, 3)] = -1; // white
    board[pos(4, 4)] = -1;
    board[pos(3, 4)] =  1; // black
    board[pos(4, 3)] =  1;
};

int Board::pos(int i, int j) const {
    return 8*i + j;
}

void Board::display() const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << (int) board[pos(i, j)] << " ";
        }
        std::cout << std::endl;
    }
}

int8_t Board::score() {
    int sum = 0;
    for(auto x : board) sum += x;
    return sum;
}

/* Renvoie si un booléen si des jetons vont être retournés dans la directions
 * donnée par un vecteur.
 *
 * Input:
 *  - i, j: position du coup
 *  - v: pair d'éléments de {-1, 0, 1} représentation une direction
 *
 * Output:
 *  la présence d'un jeton de la même couleur que le jeton en i, j dans la
 *  direction donnée
 */
bool Board::is_action_vector(int i, int j, std::pair<int, int> v) const {
    while (board[pos(i, j)] == player) {
        i += v.first;
        j += v.second;
    }
    return board[pos(i, j)] == player;
}

void Board::action_vector(int i, int j, std::pair<int, int> v) {
    if (!is_action_vector(i, j, v)) return;

    while (board[pos(i, j)] == player) {
        i += v.first;
        j += v.second;
        board[pos(i, j)] = player;
    }
    return;
}

bool Board::is_legal_move(int i, int j) const {
    if (board[pos(i, j)] != 0) return false;
    for (int d = N; d <= NW; d++) {
        if (is_action_vector(i, j, to_pair(static_cast<Direction>(d)))) return true;
    }
    return false;
}

void Board::move(int i, int j) {
    if (!is_legal_move(i, j)) return;
    board[pos(i, j)] = player;

    for (int d = N; d <= NW; d++) {
        action_vector(i, j, to_pair(static_cast<Direction>(d)));
    }

    player = -player;
}

} // end of namespace
