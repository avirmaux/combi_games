#include <iostream>

#include "reversi.hpp"
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
bool Board::is_legal_direction(int i, int j, std::pair<int8_t, int8_t> v, Color player) const {
    Color currentColor = player;
    Color oppositeColor = (player == BLACK) ? WHITE : BLACK;
    int cpt = -1; // At least one adversary token in between
    do {
        cpt++;
        i += v.first;
        j += v.second;
    } while ( i >= 0 and i < 8 and
              j >= 0 and j < 8 and
              piece(i, j) == oppositeColor);
    return  ( i >= 0 and i < 8 and
              j >= 0 and j < 8 and
              cpt > 0 and
              piece(i, j) == currentColor);
}
bool Board::is_legal_direction(int i, int j, std::pair<int8_t, int8_t> v) const {
    return is_legal_direction(i, j, v, sideToMove);
}

/* Applique un retournement le long de l'axe v si légal
 *
 * Input:
 *  - i, j: position du coup
 *  - v: pair d'éléments de {-1, 0, 1} représentation une direction
 */
void Board::flip_direction(int i, int j, std::pair<int8_t, int8_t> v) {
    Color currentColor = sideToMove;
    Color oppositeColor = (sideToMove == BLACK) ? WHITE : BLACK;

    if (!is_legal_direction(i, j, v)) return;

    do {
        set_piece(i, j, currentColor);; // First one is the actual play
        i += v.first;
        j += v.second;
    } while (piece(i, j) == oppositeColor);
}

/* Return the vector of directions in which tokens will be flipped over
 */
std::vector<std::pair<int8_t, int8_t>> Board::legal_directions(int i, int j) const {
    std::vector<std::pair<int8_t, int8_t>> res;
    if (piece(i, j) != EMPTY) return res;
    for (int d = N; d < DIRECTION_NB; d++) {
        if (is_legal_direction(i, j, to_pair(static_cast<Direction>(d)))) {
            res.push_back(to_pair(static_cast<Direction>(d)));
        }
    }
    return res;
}

// Return true if a move is legal

// Index 2D with color
bool Board::is_legal_move(int i, int j, Color player) const {
    if (piece(i, j) != EMPTY) return false;
    for (int d = N; d < DIRECTION_NB; d++)
        if (is_legal_direction(i, j, to_pair(static_cast<Direction>(d)), player))
            return true;
    return false;
}

// Index 2D
bool Board::is_legal_move(int i, int j) const {
    if (piece(i, j) != EMPTY) return false;
    for (int d = N; d < DIRECTION_NB; d++)
        if (is_legal_direction(i, j, to_pair(static_cast<Direction>(d))))
            return true;
    return false;
}

// Indexed by i \in 0 .. 63
bool Board::is_legal_move(int i, Color player) const {
    if (piece(i) != EMPTY) return false;
    for (int d = N; d < DIRECTION_NB; d++)
        if (is_legal_direction(i/8, i%8, to_pair(static_cast<Direction>(d)), player))
            return true;
    return false;
}

bool Board::is_legal_move(int i) const {
    return is_legal_move(i, side_to_move());
}

// Return all legal moves in a vector
std::vector<std::pair<int, int>> Board::legal_moves(Color player) const{
    std::vector<std::pair<int, int>> res;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (is_legal_move(i, j, player))
                res.push_back({i, j});
    return res;
}
std::vector<std::pair<int, int>> Board::legal_moves() const{
    return legal_moves(sideToMove);
}

std::vector<std::pair<int, int>> Board::childs() const {
    return legal_moves();
}

// Mouvements

void Board::make_move(int i, int j) {
    std::vector<std::pair<int8_t, int8_t>> dir = legal_directions(i, j);
    if (dir.empty()) {
        std::cerr << i << " " << j << " is not a legal move" << std::endl;
        return; // Not a legal move
    }

    for (auto v : dir) {
        flip_direction(i, j, v);
    }

    sideToMove = (sideToMove == WHITE)? BLACK : WHITE;
    if (legal_moves().empty())
        sideToMove = (sideToMove == WHITE)? BLACK : WHITE;
    nbr_pieces++;
}

void Board::make_move(std::pair<int, int> p) {
    make_move(p.first, p.second);
}

void Board::undo_move(int i, int j) {
    Color us = piece(i, j);
    Color them = (us == BLACK)? WHITE : BLACK;
    std::pair<int8_t, int8_t> dir;
    set_piece(i, j, EMPTY);
    for (int d = N; d < DIRECTION_NB; d++) {
        dir = to_pair(static_cast<Direction>(d));
        i += dir.first;
        j += dir.second;
        while (piece(i, j) == us) {
            set_piece(i, j, them);
            i += dir.first;
            j += dir.second;
        }
    }
}

void Board::undo_move(std::pair<int, int> v) {
    undo_move(v.first, v.second);
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

/* Return a random `best move` chosen by Alpha Beta pruning.
 *
 * Input:
 *  - depth, the depth of the search
 *
 *  Output:
 *  - pair (i, j) of the best_move
 */
/*
std::pair<int, int> Board::best_move(int depth) const {
    Board exploration;
    std::pair<int, int> best;
    Color best_score = 0;
    float s;

    std::vector<std::pair<int, int>> ch = childs();
    best = ch[rand()%ch.size()]; // Default is random move


    for (auto x : ch) {
        exploration = *this;
        exploration.move(x);
        s = alpha_beta(exploration, depth, -1, 1);
        if ((sideToMove == BLACK  and s > best_score) or
            (sideToMove == WHITE and s < best_score)) {
                best_score = s;
                best = x;
        }
    }
    return best;
}

std::pair<int, int> Board::best_move() const {
    return best_move(5);
}
*/
