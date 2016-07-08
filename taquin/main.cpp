#include <iostream>
#include <cstdlib>

#include "search.hpp"
#include "taquin.hpp"

void visual_tests() {
    Taquin<3> taq;
    Taquin<5> qat;

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

    TaquinSearchTree<5> astar_qt (qat);
}

int main() {
    srand(time(NULL));
    visual_tests();
    return 0;
}
