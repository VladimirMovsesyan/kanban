#include "task.h"

Task::Task() {
    this->title = this->desc = "";
}

Task::Task(const std::string &title, const std::string &desc) {
    this->title = title;
    this->desc = desc;
}

void Task::SetTitle(const std::string &title) {
    this->title = title;
}

std::string Task::GetTitle() const {
    return this->title;
}

void Task::SetDescription(const std::string &desc) {
    this->desc = desc;
}

std::string Task::GetDescription() const {
    return this->desc;
}
