#ifndef KANBAN_DRAWER_H
#define KANBAN_DRAWER_H
#include <SFML/Graphics.hpp>

const int characterSize = 50;
const int shift = 105;
const int line_thickness = 5.f;
const int minColumnWidth = 200;
const int width = 1300.f;
const int height = 1000.f;

class Drawer {
private:
    sf::Font font;
    int count_of_tables = 5;
    int toolbar_height = 90.f;

public:
    int draw();
};

#endif //KANBAN_DRAWER_H
