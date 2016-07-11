#ifndef _A_STAR_H
#define _A_STAR_H

#include <vector>
#include <set>
#include <queue>

#include "taquin.hpp"

namespace Taquin
{

template <int size_board>
class node {

    public:

    Board<size_board> board;
    node *father;
    int cost;
    int heuristic;

    friend bool operator<(const node& x, const node& y) {
        return (x.cost < y.cost);
    }

    void display() {
        node<size_board> path = *this;
        while (path.father != NULL) {
            path.board.display();
            path = *path.father;
            std::cout << " ||| " << std::endl;
        }
        // this->board.display();
        // std::cout << " ||| " << std::endl;
    }
};

template <int size_board>
std::vector<node<size_board>> childs(node<size_board> taq) {
    std::vector<node<size_board>> res;
    for (auto x : taq.board.successors()) {
            std::cout << "..." << std::endl;
            res.push_back({x, &taq, 0, x.distance()});
    }
    return res;
}

template <int size_board>
class SearchTree {

    public:

    node<size_board> init_state;

    SearchTree(Board<size_board> taq) {
        init_state = {taq, nullptr, 0, taq.distance()};
    }


    int a_star_search() {
        int cpt = 0;
        node<size_board> current_node;
        std::priority_queue<node<size_board>> heap;
        std::set<Board<size_board>> visited;
        heap.push(init_state);
        init_state.display();

        do {
            if (heap.empty()) {
                std::cout << "Empty heap, this should not happen" << std::endl;
                break;
            }
            std::cout << "Size: " << heap.size() << std::endl;
            std::cout << "Size of set: " << visited.size() << std::endl;
            cpt++;
            current_node = heap.top();
            heap.pop();
            std::cout << " POP " << std::endl;
            current_node.board.display();
            if (visited.find(current_node.board) != visited.end()) {
                std::cout << "Already visited" << std::endl;
                visited.find(current_node.board)->display();
                continue;
            }
            std::cout << "Let's visit the children" << std::endl;
            visited.insert(current_node.board);

            current_node.display();
            std::cout << " --- PUSHS ---" << std::endl;
            for (auto &c : childs(current_node)) {
                // std::cout<< " , " << std::endl;
                c.cost = current_node.cost + 1;
                heap.push(c);
            }
        } while (!(heap.top().heuristic == 0));
        // heap.top().display();
        return cpt;

        return 0;
    }


};

} // end of namespace

#endif
