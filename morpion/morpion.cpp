/* MORPION
 *
 * Structure de donnée:
 *      grille de morpion, {-1, 0, 1}
 *          vide: 0
 *          joueur 1: 1
 *          joueur 2: -1
 *
 * Algorithme: minmax
 *
 * Objectif: apprendre les algos classiques de jeux
 */

#include "morpion.hpp"

using namespace std;

Morpion::Morpion()
    : player(1), nmoves(0) {
    for (int i = 0; i < 9; i++)
            board[i] = 0;
}

int8_t Morpion::pos(int i, int j) {
    if (i < 0 or j < 0 or i > 2 or j > 2) cerr << "onoe" << endl;
    // cout << 3*i + j;
    return board[3*i + j];
}

void Morpion::display() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            switch (pos(i, j)) {
                case -1:
                    cout << " o ";
                    break;
                case 1:
                    cout << " x ";
                    break;
                case 0:
                    cout << " . ";
            }
        }
        cout << endl;
    }
}

bool Morpion::is_tie() {
    return (win() == 0) and (nmoves == 9);
}

int8_t Morpion::win() {
    for (int i = 0; i < 3; i++)
        if ((pos(i, 0) == pos(i, 1)) and (pos(i, 1) == pos(i, 2))
                and (pos(i, 0) != 0))
            return pos(i, 0);

    // Vertical
    for (int j = 0; j < 3; j++)
        if ((pos(0, j) == pos(1, j)) and (pos(1, j) == pos(2, j))
                and (pos(0, j) != 0))
            return pos(0, j);

    // Diagonales
    if (((pos(0, 0) == pos(1, 1)) and (pos(1, 1) == pos(2, 2))) or
            ((pos(0, 2) == pos(1, 1)) and (pos(1, 1) == pos(2, 0))))
        return pos(1, 1);

    return 0;
}

// Evaluate position
int8_t Morpion::eval() {
    return win();
}

bool Morpion::valid_move(int i, int j) {
    return (i >= 0 and j >= 0 and i < 3 and j < 3 and (pos(i, j) == 0));
}

// Return true or false whether the move has been made or not
bool Morpion::move(int i, int j) {
    if (valid_move(i, j)) {
        board[3*i + j] = player;
        player = -player;
        nmoves++;
        return true;
    }
    else {
        cerr << "Coup " << i << ", " << j << " invalide" << endl;
        return false;
    }
}
