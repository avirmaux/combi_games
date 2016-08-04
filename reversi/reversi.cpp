#include <iostream>

#include "reversi.hpp"
#include "misc.hpp"
// #include "search.hpp"

Board::Board() : sideToMove(BLACK), nbr_pieces(0) {
    board.fill(EMPTY);

    set_piece(3, 4, BLACK);
    set_piece(4, 3, BLACK);
    set_piece(3, 3, WHITE);
    set_piece(4, 4, WHITE);
};

void Board::display() const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch(piece(i, j)) {
                case BLACK:
                    std::cout << "● ";
                    break;
                case EMPTY:
                    std::cout << "· ";
                    break;
                case WHITE:
                    std::cout << "○ ";
                    break;
                default:
                    std::cerr << "Not known color" << std::endl;
                    break;
            }
            // std::cout << (int) board[pos(i, j)] << " ";
        }
        std::cout << std::endl;
    }
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
bool Board::is_legal_direction(int8_t i, int8_t j, Direction dir, Color player) const {
    Color us = player;
    std::pair<int8_t, int8_t> v = to_pair(dir); 
    Color them = (player == BLACK) ? WHITE : BLACK;
    int cpt = -1; // At least one adversary token in between
    do {
        cpt++;
        i += v.first;
        j += v.second;
    } while ( i >= 0 and i < 8 and
              j >= 0 and j < 8 and
              piece(i, j) == them);
    return  ( i >= 0 and i < 8 and
              j >= 0 and j < 8 and
              cpt > 0 and
              piece(i, j) == us);
}

bool Board::is_legal_direction(int8_t i, int8_t j, Direction dir)  const {
    return is_legal_direction(i, j, dir, side_to_move());
}

/* Return the vector of directions in which tokens will be flipped over
 */
int8_t Board::legal_directions(int8_t i, int8_t j) const {
    int8_t res = 0;
    if (piece(i, j) != EMPTY) return res;
    for (int8_t d = N; d < DIRECTION_NB; d++) {
        if (is_legal_direction(i, j, static_cast<Direction>(d))) {
            set_bit(res, d);
        }
    }
    return res;
}

int8_t Board::legal_directions(int8_t i) const {
    return legal_directions(i/8, i%8);
}

Move Board::make_move(int8_t i) const {
    return {i, legal_directions(i)};
}

Move Board::make_move(int8_t i, int8_t j) const {
    return make_move(8*i + j);
}

/* Applique un retournement le long de l'axe v si légal
 *
 * Input:
 *  - i, j: position du coup
 *  - v: pair d'éléments de {-1, 0, 1} représentation une direction
 */
void Board::flip_direction(int8_t i, int8_t j, Direction dir) {
    Color us = side_to_move();
    std::pair<int8_t, int8_t> v = to_pair(dir);
    Color them = (side_to_move() == BLACK) ? WHITE : BLACK;

    if (!is_legal_direction(i, j, dir)) return;

    do {
        set_piece(i, j, us);; // First one is the actual play
        i += v.first;
        j += v.second;
    } while (piece(i, j) == them);
}

// Return true if a move is legal

// Index 2D with color
//
bool Board::is_legal_move(int8_t i) const {
    return (make_move(i).from != 0);
}

// Return all legal moves in a vector of Move
std::vector<Move> Board::legal_moves(Color player) const{
    std::vector<Move> res;
    for (int i = 0; i < 8*8; i++)
            if (is_legal_move(i))
                res.push_back(make_move(i));
    return res;
}

std::vector<Move> Board::legal_moves() const{
    return legal_moves(side_to_move());
}

// Mouvements

void Board::do_move(int8_t i, int8_t j) {
    int8_t dir = legal_directions(i, j); // Bitset of legal directions
    if (dir == 0) {
        std::cerr << i << " " << j << " is not a legal move" << std::endl;
        return; // Not a legal move
    }

    for (int8_t d = 0; d < 8; d++) {
        if (is_set(dir, d)) // if d-th bit is set to 1
            flip_direction(i, j, (Direction) d);
    }

    if (!legal_moves().empty())
        sideToMove = (sideToMove == WHITE)? BLACK : WHITE;
    nbr_pieces++;
}

void Board::do_move(Move m) {
    make_move(m.to/8, m.to%8);
}

// void Board::undo_move(int8_t i, int8_t j, int8_t dirs) {
void Board::undo_move(Move m) {
    Color us = piece(m.to);
    Color them = (us == BLACK)? WHITE : BLACK;
    std::pair<int8_t, int8_t> d;
    int i = m.to/8, j = m.to%8;
    int k, l;

    set_piece(i, j, EMPTY);
    for (int8_t dir = 0; dir < 8; dir++) {
        if (!is_set(m.from, dir)) continue;
        d = to_pair(static_cast<Direction>(dir));

        k = i + d.first;
        l = j + d.second;
        while (k >= 0 and k < 8 and
               l >= 0 and l < 8 and
               piece(k, l) == us) {
            set_piece(k, l, them);
            k += d.first;
            l += d.second;
        }
        set_piece(k - d.first, l - d.second, us);
    }
}

void Board::set_piece(int i, int j, Color c) {
    board[8*i + j] = c;
}

void Board::set_piece(std::pair<int, int> p, Color c) {
    board[8 * p.first + p.second] = c;
}

// Winning and evaluation
int8_t Board::score() const {
    int sum = 0;
    for(auto x : board) sum += (x == BLACK)? 1 : -1;
    return sum;
}

/* Evaluation function
 *
 * Corner   +5
 * X-square -2
 * C-square -1
 * Sweet 16 +2
 * Other    +1
 *
 * Output: float between -1 (victory of sideToMove -1) and 1 (victory of sideToMove 1)
 */


bool Board::end_game() const {
    return (legal_moves(BLACK).empty()) and (legal_moves(WHITE).empty());
}

Color Board::win() const {
    if (!end_game()) return EMPTY;
    if (score() < 0) return WHITE;
    else return BLACK;
}
