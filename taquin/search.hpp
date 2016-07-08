#ifndef _A_STAR_H
#define _A_STAR_H

#include <vector>
#include <queue>

#include "taquin.hpp"

template <int size_board>
struct node {
    Taquin<size_board> node_state;
    Taquin<size_board> *father;
    int eval;

    friend bool operator<(node x, node y) {
        return (x.eval < y.eval);
    }
};

template <int size_board>
class TaquinSearchTree {

    public:

    node<size_board> init_state;

    TaquinSearchTree(Taquin<size_board> taq) {
        init_state = {taq, nullptr, taq.distance()};
    }

    // std::vector<int> childs

    int a_star_search() {

        return 0;
    }


};

#endif
