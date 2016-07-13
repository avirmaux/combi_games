#include <iostream>
#include <cstdlib>

#include "search.hpp"
#include "taquin.hpp"

const int size_example = 3;

int main() {
    srand(time(NULL));
    Taquin::Board<size_example> taq;
    std::vector<Taquin::Board<size_example>> shortest_path;

    for (int i = 0; i < 20; i++) {
        taq.shuffle(100);
        Taquin::SearchTree<size_example> searchTaq (taq);
        shortest_path = searchTaq.a_star_search();
        std::cout << shortest_path.size() << std::endl;
    }

    // Taquin::print_solution(shortest_path);
    // std::cout << shortest_path.size() << std::endl;
    return 0;
}
