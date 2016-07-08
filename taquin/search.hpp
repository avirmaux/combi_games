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

    std::vector<node<size_board>> childs(node<size_board> taq) {
        std::vector<node<size_board>> res;
        for (x : taq.vector_of_valid_moves())
            res.append({x, &taq, x.distance()});
        return res;
    }

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


    int a_star_search() {

        return 0;
    }


};

#endif
