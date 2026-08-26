#include "scheduler.h"
#include "Map/map.h"
#include <vector>
#include <tuple>
#include <algorithm>

Scheduler::Scheduler(const std::vector<Task>& task_list, std::vector<std::unique_ptr<Robot>>& robot_list) : task_list_(task_list), robot_list_(std::move(robot_list)) {}

Task Scheduler::assign_task() {
    Task task;
    if(task_list_.empty()) 
        return task;
    auto it = std::find_if(task_list_.begin(), task_list_.end(), [](const Task& task) {return task.type_ == Priority::HIGH && !task.assigned;});
    if(it != task_list_.end()) {
        task = *it;
        (*it).assigned = true;
        return task;
    } else {
        it = std::find_if(task_list_.begin(), task_list_.end(), [](const Task& task) {return task.type_ == Priority::MEDIUM && !task.assigned;});
        if(it != task_list_.end()) {
            task = *it;
            (*it).assigned = true;
            return task;
        } else {
            it = std::find_if(task_list_.begin(), task_list_.end(), [](const Task& task) {return task.type_ == Priority::LOW && !task.assigned;});
            if(it != task_list_.end()) {
                task = *it;
                (*it).assigned = true;
                return task;
            }
        }
    }
    return task;
}

void Scheduler::step(Map& map) {
    for(auto& robot : robot_list_) {
        State robot_state = robot->get_state();
        if(robot_state == State::Idle) {
            Task task = assign_task();
            robot->decide_path(task, map);
        }
    }

    for(auto& robot : robot_list_) {
        robot->moving();
        time_++;
    }
}

void Scheduler::print_all_robot_msg() const {
    for(const auto& robot : robot_list_) {
        robot->get_msg();
    }
}