#ifndef _A_STAR_H
#define _A_STAR_H

#include <vector>
#include <map>
#include <set>
#include <queue>

#include "taquin.hpp"

namespace Taquin
{

template <int size_board>
struct Node {

    public:

    Board<size_board> board;
    int cost;
    int heuristic;

    friend bool operator<(const Node& x, const Node& y) {
        return (x.cost + x.heuristic > y.cost + y.heuristic);
    }
};

template <int size_board>
std::vector<Node<size_board>> childs(Node<size_board> &taq) {
    std::vector<Node<size_board>> res;
    for (const auto &x : taq.board.successors()) {
        res.push_back({x, taq.cost + 1, x.distance()});
    }
    return res;
}

template <int size_board>
class SearchTree {

    public:

    Node<size_board> init_state;

    SearchTree(Board<size_board> taq) {
        init_state = {taq, 0, taq.distance()};
    }

    std::vector<Board<size_board>> a_star_search() {
        int cpt = 0;
        Node<size_board> current_node;
        std::priority_queue<Node<size_board>> heap;
        std::set<Board<size_board>> visited;
        std::map<Board<size_board>, Board<size_board>> parent_node;

        std::vector<Board<size_board>> shortest_path;
        Board<size_board> parc;

        heap.push(init_state);

        do {
            current_node = heap.top();
            heap.pop();
            if (visited.find(current_node.board) != visited.end()) {
                continue;
            }
            visited.insert(current_node.board);

            for (auto c : childs(current_node)) {
                if (visited.find(c.board) == visited.end()) {
                    parent_node[c.board] = current_node.board;
                    heap.push(c);
                }
            }
        } while (!(heap.top().board.is_solved()));


        parc = heap.top().board;
        shortest_path.push_back(parc);
        while (parc != init_state.board) {
            parc = parent_node[parc];
            shortest_path.push_back(parc);
            cpt++;
        }
        return shortest_path;
    }


};

template <int size_board>
void print_solution(std::vector<Board<size_board>> v) {
    for (int i = v.size()-1; i >= 0; i--) {
        v[i].display();
        std::cout << std::endl;
    }
}
} // end of namespace

#endif
