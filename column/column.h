#ifndef KANBAN_COLUMN_H
#define KANBAN_COLUMN_H
#include "../task/task.h"
#include <iostream>
#include <vector>
class Column {
private:
    std::string name;
    int color;
    std::vector<Task> tasks;

public:
    Column();
    Column(const std::string &, int, int, int);

    ~Column() = default;

    void SetName(const std::string &);
    std::string GetName();
    void SetColor(int, int, int);
    void SetColor(int);
    int GetColor() const;
    void SetTasks(std::vector<Task>);
    std::vector<Task> GetTasks();
    void AddTask(Task &task);
};

#endif//KANBAN_COLUMN_H
