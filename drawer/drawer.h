#ifndef KANBAN_DRAWER_H
#define KANBAN_DRAWER_H
#include <SFML/Graphics.hpp>
class Drawer {
private:
    sf::Font font;

    int count_of_tables = 5;
    int width = 1300.f;
    int height = 1000.f;

    int toolbar_height = 90.f;
public:
    int draw();
};

#endif //KANBAN_DRAWER_H
