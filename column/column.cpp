#include "column.h"

Column::Column() {
    this->name = "";
    this->color = 0;
    tasks.clear();
}

Column::Column(const std::string &name, int red, int green, int blue) {
    this->name = name;
    this->color = (red << 16) + (green << 8) + blue;
    tasks.clear();
}

void Column::SetName(const std::string &name) {
    this->name = name;
}

std::string Column::GetName() {
    return this->name;
}

void Column::SetColor(int color) {
    this->color = color;
}

void Column::SetColor(int red, int green, int blue) {
    this->color = (red << 16) + (green << 8) + blue;
}

int Column::GetColor() const {
    return this->color;
}

void Column::SetTasks(std::vector<Task> tasks) {
    this->tasks.clear();
    for (auto &task: tasks) {
        this->tasks.push_back(task);
    }
}

std::vector<Task> Column::GetTasks() {
    return this->tasks;
}

void Column::AddTask(Task &task) {
    this->tasks.push_back(task);
}
