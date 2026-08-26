#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "Task/task.h"
#include "Robot/robot.h"
#include <memory>
class Scheduler {
    std::vector<Task> task_list_;
    std::vector<std::unique_ptr<Robot>> robot_list_;
    int time_ = 0;
    int charge_count_ = 0;
    int dead_count_ = 0;
public:
    Scheduler(const std::vector<Task>& task_list, std::vector<std::unique_ptr<Robot>>& robot_list, const Map& map);
    void step(Map& map);
    Task* assign_task();
    void print_all_robot_msg() const;
    void print_all_task_msg() const;
    void print_map_with_robot(const Map& map) const;
    bool all_done() const;
    bool all_dead() const;
    void print_statistics() const;
};


#endif