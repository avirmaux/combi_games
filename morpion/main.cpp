#include "minmax.hpp"
#include "morpion.hpp"

#include <iostream>
#include <cstring>
#include <cstdint>
#include <algorithm> //min and max

using namespace std;

pair<int, int> CPU_move(Morpion game) {
    return game.best_move();
}

int main () {
    int i, j;
    pair<int, int> p;
    Morpion game;

    srand(time(NULL));

    // cout << (int) min_max(game) << endl;

    // game.player = -1;

    while (!(game.is_tie()) and (game.win() == 0)) {
        game.display();
        cout << endl;
        if (game.player == 1) {
            cout << "Enter a move" << endl;
            cin >> i >> j;
            game.move(i, j);
        }
        else {
            p = CPU_move(game);
            game.move(p.first, p.second);
        }
    }
    game.display();
    if (game.win())
        cout << "Winner is player " << (int) game.win() << endl;
    else
        cout << "Tie" << endl;

    // */
    return 0;
}
