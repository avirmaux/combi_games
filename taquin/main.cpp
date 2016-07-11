#include <iostream>
#include <cstdlib>

#include "search.hpp"
#include "taquin.hpp"

int main() {
    srand(time(NULL));
    Taquin::Board<3> taq;
    std::vector<Taquin::Board<3>> shortest_path;

    taq.shuffle(100);
    Taquin::SearchTree<3> searchTaq (taq);
    shortest_path = searchTaq.a_star_search();

    Taquin::print_solution(shortest_path);
    std::cout << shortest_path.size() << std::endl;
    return 0;
}
