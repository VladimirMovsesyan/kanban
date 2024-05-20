#ifndef KANBAN_TASK_H
#define KANBAN_TASK_H

#include <iostream>

class Task {
private:
    std::string title;
    std::string desc;

public:
    Task();
    Task(const std::string &, const std::string &);

    ~Task() = default;

    void SetTitle(const std::string &);
    std::string GetTitle() const;
    void SetDescription(const std::string &);
    std::string GetDescription() const;
};

#endif//KANBAN_TASK_H
