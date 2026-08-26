#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "Task/task.h"
#include "Robot/robot.h"
#include <memory>
class Scheduler {
    std::vector<Task> task_list_;
    std::vector<std::unique_ptr<Robot>> robot_list_;
    int time_;
public:
    Scheduler(const std::vector<Task>& task_list, std::vector<std::unique_ptr<Robot>>& robot_list);
    void step(Map& map);
    Task* assign_task();
    void print_all_robot_msg() const;
    void print_all_task_msg() const;
};


#endif