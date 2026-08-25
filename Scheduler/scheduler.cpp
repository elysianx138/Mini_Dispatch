#include "scheduler.h"
#include "Map/map.h"
#include <vector>
#include <tuple>

Task Scheduler::assign_task() {
    if(task_list_.empty())
        return;
    for(const auto& task : task_list_) {
        if(!task.done) {
            if(task.type_ == Priority::HIGH)
                return task;
            if(task.type_ == Priority::MEDIUM)
                return task;
            if(task.type_ == Priority::LOW)
                return task;
        }
    }
    return;
}

void Scheduler::step(Map& map) {
    for(const auto& robot : robot_list_) {
        State robot_state = robot->get_state();
        if(robot_state == State::Idle) {
            Task task = assign_task();
            robot->decide_path(task, map);
        }
    }
}