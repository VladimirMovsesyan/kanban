#include "task.h"

void Task::SetTitle(const std::string &title) {
    this->title = title;
}

std::string Task::GetTitle() {
    return this->title;
}

void Task::SetDescription(const std::string &desc) {
    this->desc = desc;
}

std::string Task::GetDescription() {
    return this->desc;
}
