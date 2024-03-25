#include "drawer.h"


int Drawer::draw() {

    int table_width = width / count_of_tables;

    if (table_width < minColumnWidth) {
        return 1;
    }

    if (!font.loadFromFile("arial.ttf")) {
        return 2;
    }

    sf::RenderWindow window(sf::VideoMode(width, height), "Main screen");

    sf::RectangleShape line_bar(sf::Vector2f(width, line_thickness));
    line_bar.setPosition(0, toolbar_height);

    sf::Text programName;
    programName.setFont(font);
    programName.setString("KANBAN");
    programName.setCharacterSize(characterSize);
    programName.setPosition(width / 2 - shift, 0);

    sf::RectangleShape* lines_of_tables = new sf::RectangleShape[count_of_tables - 1];
    for (int i = 0; i < count_of_tables - 1; ++i) {
        lines_of_tables[i].setSize(sf::Vector2f(height, line_thickness));
        lines_of_tables[i].setPosition(table_width * (i + 1), toolbar_height);
        lines_of_tables[i].setRotation(toolbar_height);
    }

    sf::RectangleShape newTask_button(sf::Vector2f(100, 70));
    newTask_button.setPosition(10, 10);

    sf::RectangleShape newTable_button(sf::Vector2f(100, 70));
    newTable_button.setPosition(width - 100 - 10, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(line_bar);

        window.draw(programName);

        window.draw(newTask_button);
        window.draw(newTable_button);

        for (int i = 0; i < count_of_tables - 1; ++i) {
            window.draw(lines_of_tables[i]);
        }

        window.display();
    }
    return 0;
}
