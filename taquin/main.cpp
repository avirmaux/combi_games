#include <iostream>
#include <cstdlib>

#include "search.hpp"
#include "taquin.hpp"

void visual_tests() {
    Taquin::Board<3> taq;
    Taquin::Board<5> qat;

    taq.display();
    taq.move(BOTTOM);
    std::cout << std::endl;
    taq.display();
    taq.move(RIGHT);
    std::cout << std::endl;
    taq.display();
    taq.move(LEFT);
    std::cout << std::endl;
    taq.display();
    taq.move(UP);
    std::cout << std::endl;
    taq.display();
    std::cout << std::endl;
    std::cout << taq.distance() << std::endl;
    std::cout << std::endl;

    std::cout << std::endl;
    taq.shuffle(201);
    taq.display();
    std::cout << std::endl;
    std::cout << taq.distance() << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    qat.shuffle(201);
    qat.display();
    std::cout << std::endl;
    std::cout << taq.distance() << std::endl;

    Taquin::SearchTree<5> astar_qt (qat);
    astar_qt.init_state.display();
    // Taquin::childs(astar_qt.init_state);
}

int main() {
    srand(time(NULL));
    // visual_tests();
    Taquin::Board<3> taq;

    taq.shuffle(7);
    Taquin::SearchTree<3> searchTaq (taq);
    std::cout << searchTaq.a_star_search() << std::endl;
    return 0;
}
