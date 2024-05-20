#include "drawer.h"
#include "../column/column.h"

#include <iostream>

int Drawer::draw(std::vector<Column> &columns) {
    float columnWidth = static_cast<float>(width) / static_cast<float>(columnNumber);

    if (columnWidth < minColumnWidth) {
        return 1;
    }

    if (!font.loadFromFile("arial.ttf")) {
        return 2;
    }

    sf::RenderWindow window(sf::VideoMode(width, height), "Kanban");

    sf::RectangleShape line_bar(sf::Vector2f(width, line_thickness));
    line_bar.setPosition(0, toolbarHeight);

    sf::Text programName;
    programName.setFont(font);
    programName.setString("VIPERR");
    programName.setCharacterSize(characterSize);
    programName.setPosition(width / 2.f - shift, 0);


    sf::RectangleShape newTask_button(sf::Vector2f(100, 70));
    newTask_button.setPosition(10, 10);

    sf::RectangleShape newColumn_button(sf::Vector2f(100, 70));
    newColumn_button.setPosition(width - 100 - 10, 10);
    int cnt = 0;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.scancode == sf::Keyboard::Scan::Down) {
                scroll_pointer++;
            }
            if (event.key.scancode == sf::Keyboard::Scan::Up) {
                if (scroll_pointer > 0) {
                    scroll_pointer--;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.x > 10 && event.mouseButton.x < 110 &&
                event.mouseButton.y > 10 && event.mouseButton.y < 80) {
                // Creation task clicked
                std::cerr << cnt++ << std::endl;
                int col;
                auto task = add_task(col);
                if (!task.GetTitle().empty())
                    columns[col].AddTask(task);
            }

            if (event.mouseButton.x > width - 100 - 10 && event.mouseButton.x < width - 10 &&
                event.mouseButton.y > 10 && event.mouseButton.y < 80) {
                // Creation column clicked
            }

            if (event.mouseButton.y > toolbarHeight) {
                int tempCol = event.mouseButton.x / columnWidth;
                int col = event.mouseButton.x / columnWidth;
                auto tasks = columns[col].GetTasks();
                size_t taskNumber = (event.mouseButton.y - toolbarHeight) / (static_cast<float>(width) / static_cast<float>(columnNumber) / 2) + scroll_pointer;
                if (taskNumber < tasks.size()) {
                    Task &editableTask = tasks[taskNumber];
                    edit_task(editableTask, col);
                    if (col != tempCol) {
                        tasks.erase(tasks.begin() + taskNumber);
                    }
                    columns[tempCol].SetTasks(tasks);
                    if (col != tempCol && col != -1) {
                        auto tasks = columns[col].GetTasks();
                        tasks.push_back(editableTask);
                        columns[col].SetTasks(tasks);
                    }
                    std::cerr << col << ' ' << tempCol << std::endl;
                }
            }
        }

        window.clear();

        window.draw(line_bar);

        window.draw(programName);

        window.draw(newTask_button);
        window.draw(newColumn_button);
        draw_tasks(window, columns);
        window.display();
    }
    return 0;
}

void Drawer::draw_tasks(sf::RenderWindow &window, std::vector<Column> &columns) {
    float columnWidth = static_cast<float>(width) / static_cast<float>(columnNumber);
    std::vector<sf::Color> columnColor = {sf::Color(25, 25, 25, 128), sf::Color(0, 128, 200, 128), sf::Color(128, 200, 128, 128)};


    std::vector<sf::RectangleShape> lines_of_tables(columnNumber);
    for (int i = 0; i < columnNumber; ++i) {
        lines_of_tables[i].setSize(sf::Vector2f(height, line_thickness));
        lines_of_tables[i].setPosition(columnWidth * static_cast<float>(i + 1), toolbarHeight);
        lines_of_tables[i].setRotation(toolbarHeight);
    }

    for (int i = 0; i < columnNumber; ++i) {
        auto tasks = columns[i].GetTasks();
        for (size_t j = scroll_pointer; j < tasks.size(); j++) {
            auto shape = sf::RectangleShape(sf::Vector2f(columnWidth - 15, columnWidth / 2));
            shape.setPosition(5 + columnWidth * i, 100 + (j - scroll_pointer) * (228));
            shape.setFillColor(columnColor[i]);
            window.draw(shape);

            auto text = sf::Text();
            text.setFont(font);
            text.setCharacterSize(characterSize / 2);
            text.setString(tasks[j].GetTitle());
            text.setPosition((shape.getPosition().x * 2 + shape.getSize().x) / 2,
                             (shape.getPosition().y * 2 + shape.getSize().y) / 2);


            window.draw(text);
        }
        window.draw(lines_of_tables[i]);
    }
}

#define DELETE_KEY 8

// TODO: restrict ability to change windows size
Task Drawer::add_task(int &toColumn) {
    sf::RenderWindow window(sf::VideoMode(400, 300), "Add Task");
    std::string title, desc;
    bool titleSelected = true;

    std::vector<sf::Vector2f> selectedColumnVector = {{292, 227}, {292, 242}, {292, 257}};
    int selectedColumn = 0;

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (titleSelected) {
                    if (event.key.code == DELETE_KEY) {
                        if (!title.empty()) {
                            title.erase(title.end() - 1);
                        }
                    } else {
                        title += static_cast<char>(event.key.code);
                    }
                } else {
                    if (event.key.code == DELETE_KEY) {
                        if (!desc.empty()) {
                            desc.erase(desc.end() - 1);
                        }
                    } else {
                        desc += static_cast<char>(event.key.code);
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.x > 50 && event.mouseButton.x < 350 &&
                    event.mouseButton.y > 50 && event.mouseButton.y < 100) {
                    titleSelected = true;
                }

                if (event.mouseButton.x > 50 && event.mouseButton.x < 350 &&
                    event.mouseButton.y > 120 && event.mouseButton.y < 170) {
                    titleSelected = false;
                }

                if (event.mouseButton.x > 150 && event.mouseButton.x < 250 &&
                    event.mouseButton.y > 220 && event.mouseButton.y < 250) {
                    window.close();
                    toColumn = selectedColumn;
                    return {title, desc};
                }

                if (event.mouseButton.x > 290 && event.mouseButton.x < 350 &&
                    event.mouseButton.y > 225 && event.mouseButton.y < 240) {
                    selectedColumn = 0;
                }

                if (event.mouseButton.x > 290 && event.mouseButton.x < 350 &&
                    event.mouseButton.y > 240 && event.mouseButton.y < 255) {
                    selectedColumn = 1;
                }

                if (event.mouseButton.x > 290 && event.mouseButton.x < 350 &&
                    event.mouseButton.y > 255 && event.mouseButton.y < 270) {
                    selectedColumn = 2;
                }
            }
        }

        window.clear();

        auto titleField = sf::RectangleShape(sf::Vector2f(300, 50));
        titleField.setPosition(50, 50);
        window.draw(titleField);

        auto descField = sf::RectangleShape(sf::Vector2f(300, 50));
        descField.setPosition(50, 120);
        window.draw(descField);

        sf::Text titleText;
        titleText.setCharacterSize(characterSize / 2);
        titleText.setFont(font);
        if (!title.empty()) {
            titleText.setString(title);
        } else {
            titleText.setString("Title...");
        }
        titleText.setPosition(50, 60);
        titleText.setFillColor(sf::Color::Black);
        window.draw(titleText);

        sf::Text descText;
        descText.setCharacterSize(characterSize / 2);
        descText.setFont(font);
        if (!desc.empty()) {
            descText.setString(desc);
        } else {
            descText.setString("Description...");
        }

        descText.setPosition(50, 130);
        descText.setFillColor(sf::Color::Black);
        window.draw(descText);

        auto button = sf::RectangleShape(sf::Vector2f(95, 30));
        button.setPosition(150, 220);
        window.draw(button);

        sf::Text enterText;
        enterText.setCharacterSize(characterSize / 2);
        enterText.setFont(font);
        enterText.setString("Enter");
        enterText.setPosition(167, 220);
        enterText.setFillColor(sf::Color::Black);
        window.draw(enterText);



        sf::Text notStartedText;
        notStartedText.setCharacterSize(characterSize / 3);
        notStartedText.setFont(font);
        notStartedText.setString("Not started");
        notStartedText.setPosition(300, 220);
        notStartedText.setFillColor(sf::Color::White);
        window.draw(notStartedText);

        sf::Text inProgressText;
        inProgressText.setCharacterSize(characterSize / 3);
        inProgressText.setFont(font);
        inProgressText.setString("In progress");
        inProgressText.setPosition(300, 235);
        inProgressText.setFillColor(sf::Color(0, 128, 200));
        window.draw(inProgressText);

        sf::Text doneText;
        doneText.setCharacterSize(characterSize / 3);
        doneText.setFont(font);
        doneText.setString("Done");
        doneText.setPosition(300, 250);
        doneText.setFillColor(sf::Color::Green);
        window.draw(doneText);

        auto notStartedCircle = sf::CircleShape(5);
        notStartedCircle.setPosition(290, 225);
        notStartedCircle.setFillColor(sf::Color::White);
        window.draw(notStartedCircle);

        auto inProgressCircle = sf::CircleShape(5);
        inProgressCircle.setPosition(290, 240);
        inProgressCircle.setFillColor(sf::Color::White);
        window.draw(inProgressCircle);

        auto doneCircle = sf::CircleShape(5);
        doneCircle.setPosition(290, 255);
        doneCircle.setFillColor(sf::Color::White);
        window.draw(doneCircle);

        auto selectedCircle = sf::CircleShape(3);
        selectedCircle.setPosition(selectedColumnVector[selectedColumn]);
        selectedCircle.setFillColor(sf::Color::Black);
        window.draw(selectedCircle);


        window.display();
    }

    return Task{};
}

void Drawer::edit_task(Task &task, int &col) {
    sf::RenderWindow window(sf::VideoMode(400, 300), "Edit Task");
    std::string title = task.GetTitle(), desc = task.GetDescription();
    std::cerr << "title: " << title << std::endl;
    bool titleSelected = true;

    std::vector<sf::Vector2f> selectedColumnVector = {{292, 227}, {292, 242}, {292, 257}};
    int selectedColumn = col;

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered) {
                if (titleSelected) {
                    if (event.key.code == DELETE_KEY) {
                        if (!title.empty()) {
                            title.erase(title.end() - 1);
                        }
                    } else {
                        title += static_cast<char>(event.key.code);
                    }
                } else {
                    if (event.key.code == DELETE_KEY) {
                        if (!desc.empty()) {
                            desc.erase(desc.end() - 1);
                        }
                    } else {
                        desc += static_cast<char>(event.key.code);
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.x > 50 && event.mouseButton.x < 350 &&
                    event.mouseButton.y > 50 && event.mouseButton.y < 100) {
                    titleSelected = true;
                }

                if (event.mouseButton.x > 50 && event.mouseButton.x < 350 &&
                    event.mouseButton.y > 120 && event.mouseButton.y < 170) {
                    titleSelected = false;
                }

                if (event.mouseButton.x > 150 && event.mouseButton.x < 250 &&
                    event.mouseButton.y > 220 && event.mouseButton.y < 250) {
                    window.close();
                    if (!title.empty())
                        task.SetTitle(title);
                    task.SetDescription(desc);
                    col = selectedColumn;
                    return;
                }

                if (event.mouseButton.x > 290 && event.mouseButton.x < 350 &&
                    event.mouseButton.y > 225 && event.mouseButton.y < 240) {
                    selectedColumn = 0;
                }

                if (event.mouseButton.x > 290 && event.mouseButton.x < 350 &&
                    event.mouseButton.y > 240 && event.mouseButton.y < 255) {
                    selectedColumn = 1;
                }

                if (event.mouseButton.x > 290 && event.mouseButton.x < 350 &&
                    event.mouseButton.y > 255 && event.mouseButton.y < 270) {
                    selectedColumn = 2;
                }

                if (event.mouseButton.x > 10 && event.mouseButton.x < 90 &&
                    event.mouseButton.y > 220 && event.mouseButton.y < 250) {
                    col = -1;
                    return;
                }
            }
        }

        window.clear();

        auto titleField = sf::RectangleShape(sf::Vector2f(300, 50));
        titleField.setPosition(50, 50);
        window.draw(titleField);

        auto descField = sf::RectangleShape(sf::Vector2f(300, 50));
        descField.setPosition(50, 120);
        window.draw(descField);

        sf::Text titleText;
        titleText.setCharacterSize(characterSize / 2);
        titleText.setFont(font);
        if (!title.empty()) {
            titleText.setString(title);
        } else {
            titleText.setString("Title...");
        }
        titleText.setPosition(50, 60);
        titleText.setFillColor(sf::Color::Black);
        window.draw(titleText);

        sf::Text descText;
        descText.setCharacterSize(characterSize / 2);
        descText.setFont(font);
        if (!desc.empty()) {
            descText.setString(desc);
        } else {
            descText.setString("Description...");
        }

        descText.setPosition(50, 130);
        descText.setFillColor(sf::Color::Black);
        window.draw(descText);

        auto button = sf::RectangleShape(sf::Vector2f(95, 30));
        button.setPosition(150, 220);
        window.draw(button);

        sf::Text enterText;
        enterText.setCharacterSize(characterSize / 2);
        enterText.setFont(font);
        enterText.setString("Enter");
        enterText.setPosition(167, 220);
        enterText.setFillColor(sf::Color::Black);
        window.draw(enterText);

        auto delButton = sf::RectangleShape(sf::Vector2f(85, 30));
        delButton.setPosition(10, 220);
        delButton.setFillColor(sf::Color(200, 45, 45));
        window.draw(delButton);

        sf::Text delText;
        delText.setCharacterSize(characterSize / 2);
        delText.setFont(font);
        delText.setString("Delete");
        delText.setPosition(15, 220);
        delText.setFillColor(sf::Color::Black);
        window.draw(delText);

        sf::Text notStartedText;
        notStartedText.setCharacterSize(characterSize / 3);
        notStartedText.setFont(font);
        notStartedText.setString("Not started");
        notStartedText.setPosition(300, 220);
        notStartedText.setFillColor(sf::Color::White);
        window.draw(notStartedText);

        sf::Text inProgressText;
        inProgressText.setCharacterSize(characterSize / 3);
        inProgressText.setFont(font);
        inProgressText.setString("In progress");
        inProgressText.setPosition(300, 235);
        inProgressText.setFillColor(sf::Color(0, 128, 200));
        window.draw(inProgressText);

        sf::Text doneText;
        doneText.setCharacterSize(characterSize / 3);
        doneText.setFont(font);
        doneText.setString("Done");
        doneText.setPosition(300, 250);
        doneText.setFillColor(sf::Color(128, 200, 128));
        window.draw(doneText);

        auto notStartedCircle = sf::CircleShape(5);
        notStartedCircle.setPosition(290, 225);
        notStartedCircle.setFillColor(sf::Color::White);
        window.draw(notStartedCircle);

        auto inProgressCircle = sf::CircleShape(5);
        inProgressCircle.setPosition(290, 240);
        inProgressCircle.setFillColor(sf::Color::White);
        window.draw(inProgressCircle);

        auto doneCircle = sf::CircleShape(5);
        doneCircle.setPosition(290, 255);
        doneCircle.setFillColor(sf::Color::White);
        window.draw(doneCircle);

        auto selectedCircle = sf::CircleShape(3);
        selectedCircle.setPosition(selectedColumnVector[selectedColumn]);
        selectedCircle.setFillColor(sf::Color::Black);
        window.draw(selectedCircle);


        window.display();
    }
}
