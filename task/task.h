#ifndef KANBAN_TASK_H
#define KANBAN_TASK_H

#include <iostream>

class Task {
private:
    std::string title;
    std::string desc;

public:
    Task();
    Task(std::string &, std::string &);

    ~Task() = default;

    void SetTitle(const std::string &);
    std::string GetTitle();
    void SetDescription(const std::string &);
    std::string GetDescription();
};

#endif//KANBAN_TASK_H
