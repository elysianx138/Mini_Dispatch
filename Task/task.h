#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>


enum class Priority {LOW, MEDIUM, HIGH, PriorityCount};

std::string Priority_to_string(Priority priority);


// 后续(x_ ,y_)
// x作为行, y作为列

struct Task{
    int x_;
    int y_;
    int required_power_;
    Priority type_;
    bool done;
    bool assigned;

    Task();
    Task(int x, int y);
    Task(int x, int y, const Priority& type);   
};
#endif