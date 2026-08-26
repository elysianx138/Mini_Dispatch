#include "scheduler.h"
#include "Map/map.h"
#include <vector>
#include <tuple>
#include <algorithm>

Scheduler::Scheduler(const std::vector<Task>& task_list, std::vector<std::unique_ptr<Robot>>& robot_list) : task_list_(task_list), robot_list_(std::move(robot_list)) {}

Task* Scheduler::assign_task() {
    Task* task = nullptr;
    if(task_list_.empty()) 
        return nullptr;
    auto it = std::find_if(task_list_.begin(), task_list_.end(), [](const Task& task) {return task.type_ == Priority::HIGH && !task.assigned && !task.done;});
    if(it != task_list_.end()) {
        task = &(*it);
        (*it).assigned = true;
        return task;
    } else {
        it = std::find_if(task_list_.begin(), task_list_.end(), [](const Task& task) {return task.type_ == Priority::MEDIUM && !task.assigned && !task.done;});
        if(it != task_list_.end()) {
            task = &(*it);
            (*it).assigned = true;
            return task;
        } else {
            it = std::find_if(task_list_.begin(), task_list_.end(), [](const Task& task) {return task.type_ == Priority::LOW && !task.assigned && !task.done;});
            if(it != task_list_.end()) {
                task = &(*it);
                (*it).assigned = true;
                return task;
            }
        }
    }
    return nullptr;
}

void Scheduler::step(Map& map) {
    for(auto& robot : robot_list_) {
        State robot_state = robot->get_state();
        if(robot_state == State::Idle) {
            Task* task = assign_task();
            if(task)
                robot->receive_task(task, map);
        }
    }

    for(auto& robot : robot_list_) {
        robot->step(map);
        time_++;
    }
}
// 1.搜索所有空闲机器人
// 2. 分配任务, 行动

void Scheduler::print_all_robot_msg() const {
    for(const auto& robot : robot_list_) {
        robot->get_msg();
    }
}

void Scheduler::print_all_task_msg() const {
    for(const auto& task : task_list_) {
        std::cout<<"任务坐标: "<<task.x_<<": "<<task.y_<<" "<<"任务优先级: "<<Priority_to_string(task.type_)<<" "<<"任务是否完成: "<<task.done<<" "<<"任务是否分配: "<<task.assigned<<std::endl;
    }
}