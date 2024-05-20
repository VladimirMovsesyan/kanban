#include <iostream>
#include "drawer/drawer.h"
#include "column/column.h"

int main() {
    Drawer drawer;
    Task task1(std::string("1"), std::string("1"));
    Task task2(std::string("2"), std::string("2"));
    Task task3(std::string("3"), std::string("3"));
    Task task4(std::string("4"), std::string("4"));
    std::vector<Column> columns(3);
    columns[0].AddTask(task1);
    columns[0].AddTask(task2);
    columns[0].AddTask(task3);
    columns[0].AddTask(task4);
    columns[1].AddTask(task1);
    for(auto &col: columns) {
        col.SetName("Column");
    }
    drawer.draw(columns);

    return 0;
}