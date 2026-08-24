#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <string>


enum class Priority {LOW, MEDIUM, HIGH};

std::string Priority_to_string(Priority priority);


struct Task{
    int x_;
    int y_;
    Priority type_;
    bool done;

    Task(int x, int y, const Priority& type);
    void check_station();    
};
#endif