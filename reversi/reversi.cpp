#include "reversi.hpp"

namespace Reversi {

/* to_pair
 *
 * Translate a Direction to a vector, <x component, y component>
 *
 * For exemple South East is {1, -1}
 */
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

    board[pos(3, 4)] =  1; // black
    board[pos(4, 3)] =  1;
    board[pos(3, 3)] = -1; // white
    board[pos(4, 4)] = -1;
};

int Board::pos(int i, int j) const {
    return 8*i + j;
}

void Board::display() const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch(board[pos(i, j)]) {
                case 1:
                    std::cout << "○ ";
                    break;
                case 0:
                    std::cout << "· ";
                    break;
                case -1:
                    std::cout << "● ";
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
bool Board::is_action_vector(int i, int j, std::pair<int, int> v) const {
    int cpt = -1; // At least one adversary token in between
    do {
        cpt++;
        i += v.first;
        j += v.second;
    } while ( i >= 0 and i < 8 and
              j >= 0 and j < 8 and
              board[pos(i, j)] == -player);
    return  ( i >= 0 and i < 8 and
              j >= 0 and j < 8 and
              cpt > 0 and
              board[pos(i, j)] == player);
}

/* Applique un retournement le long de l'axe v si légal
 *
 * Input:
 *  - i, j: position du coup
 *  - v: pair d'éléments de {-1, 0, 1} représentation une direction
 */
void Board::action_vector(int i, int j, std::pair<int, int> v) {
    if (!is_action_vector(i, j, v)) return;

    do {
        board[pos(i, j)] = player; // First one is the actual play
        i += v.first;
        j += v.second;
    } while (board[pos(i, j)] == -player);
}

/* Return the vector of directions in which tokens will be flipped over
 */
std::vector<std::pair<int, int>> Board::legal_directions(int i, int j) const {
    std::vector<std::pair<int, int>> res;
    if (board[pos(i, j)] != 0) return res;
    for (int d = N; d <= NW; d++) {
        if (is_action_vector(i, j, to_pair(static_cast<Direction>(d)))) {
            res.push_back(to_pair(static_cast<Direction>(d)));
        }
    }
    return res;
}

bool Board::is_legal_move_fast(int i, int j) const {
    if (board[pos(i, j)] != 0) return false;
    for (int d = N; d <= NW; d++)
        if (is_action_vector(i, j, to_pair(static_cast<Direction>(d))))
            return true;
    return false;
}

// Return true if a move is legal
bool Board::is_legal_move(int i, int j) const {
    return !(legal_directions(i, j).empty());
}

std::vector<std::pair<int, int>> Board::vector_of_legal_moves() const{
    std::vector<std::pair<int, int>> res;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (is_legal_move_fast(i, j))
                res.push_back({i, j});
    return res;
}

std::vector<std::pair<int, int>> Board::childs() const {
    return vector_of_legal_moves();
}

void Board::move(int i, int j) {
    std::vector<std::pair<int, int>> dir = legal_directions(i, j);
    if (dir.empty()) {
        std::cerr << i << " " << j << " is not a legal move" << std::endl;
        return; // Not a legal move
    }

    for (auto v : dir) {
        action_vector(i, j, v);
    }

    player = -player;
}

void Board::move(std::pair<int, int> p) {
    move(p.first, p.second);
}


// WINNING AND EVALUATION
int8_t Board::eval() const {
    int sum = 0;
    for(auto x : board) sum += x;
    return sum;
}

bool Board::is_finished() const {
    return (vector_of_legal_moves().empty());
}

int8_t Board::win() const {
    if (!is_finished()) return 0;
    return (eval() > 0) - (eval() < 0);
}

/* Return a random `best move` for Alpha Beta pruning.
 *
 * Input:
 *  - depth, the depth of the search
 *
 *  Output:
 *  - pair (i, j) of the best_move
 */
std::pair<int, int> Board::best_move(int depth) const {
    Board exploration;
    std::pair<int, int> best;
    int8_t s, best_score = 0;

    std::vector<std::pair<int, int>> ch = childs();
    best = ch[rand()%ch.size()]; // Default is random move


    for (auto x : ch) {
        exploration = *this;
        exploration.move(x);
        s = alpha_beta(exploration, depth, -64, 64);
        if ((player == 1  and s > best_score) or
            (player == -1 and s < best_score)) {
                best_score = s;
                best = x;
        }
    }
    return best;
}

std::pair<int, int> Board::best_move() const {
    return best_move(4);
}

} // end of namespace
