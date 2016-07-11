void visual_tests() {
    Taquin::Board<3> taq;
    Taquin::Board<5> qat;

    Taquin::Board<4> taquin_41;
    Taquin::Board<4> taquin_42;

    taquin_41.shuffle(50);
    taquin_42.shuffle(50);

    taquin_41.display();
    std::cout << " < " << std::endl;
    taquin_42.display();
    std::cout << " = " << std::endl;
    std::cout << (taquin_41 < taquin_42) << std::endl;

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

