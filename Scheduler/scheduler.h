#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "Task/task.h"
#include "Robot/robot.h"
#include <memory>
class Scheduler {
    std::vector<Task> task_list_;
    std::vector<std::unique_ptr<Robot>> robot_list_;

public:
    void step(Map& map);
    Task assign_task();
};


#endif