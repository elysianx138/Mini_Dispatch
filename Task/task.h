#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <string>


enum class Priority {LOW, MEDIUM, HIGH};

std::string Priority_to_string(Priority priority);


// 后续(x_ ,y_)
// x作为行, y作为列

struct Task{
    int x_;
    int y_;
    Priority type_;
    bool done;

    Task(int x, int y, const Priority& type);
    void check_station();    
};
#endif