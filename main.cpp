#include <iostream>
#include "drawer/drawer.h"

int main(int argc, char** argv) {
    std::cout << argv[0];
    Drawer drawer;
    drawer.draw();

    return 0;
}
