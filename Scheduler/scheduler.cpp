#include "scheduler.h"
#include "Map/map.h"
#include "Utils/except.h"
#include "Utils/logger.h"
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>

Scheduler::Scheduler(const std::vector<Task>& task_list, std::vector<std::unique_ptr<Robot>>& robot_list, const Map& map) : task_list_(task_list), robot_list_(std::move(robot_list)) {
    for(auto& robot : robot_list_) {
        if(robot->x_pos()<0||robot->y_pos()<0||robot->x_pos()>=map.row()||robot->y_pos()>=map.col()) {
            throw Robot_error("机器人初始位置不合法", robot->get_id());
        }
    }
}

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

    std::vector<State> prev;
    for (auto& robot : robot_list_)
        prev.push_back(robot->get_state());

    for(auto& robot : robot_list_) {
        State robot_state = robot->get_state();
        if(robot_state == State::Idle) {
            Task* task = assign_task();
            if(task) {
                robot->receive_task(task, map);
                log_event(time_, "INFO", "机器人" + std::to_string(robot->get_id()) + " 领取任务 (" + std::to_string(task->x_) + "," + std::to_string(task->y_) +") [" + Priority_to_string(task->type_) + "]");
            }
        }
    }

    for(auto& robot : robot_list_)
        robot->step(map);
        time_++;

    for (size_t i = 0; i < robot_list_.size(); i++) {
        State now = robot_list_[i]->get_state();
        if (now != prev[i]) {
            log_event(time_, "INFO", "机器人" + std::to_string(robot_list_[i]->get_id()) + ": " + State_to_string(prev[i]) + " → " + State_to_string(now));
            if (now == State::Charging) charge_count_++;
            if (now == State::DEAD) dead_count_++;
        }
    }
}
// 1.搜索所有空闲机器人
// 2. 分配任务, 行动
// 日志打印

bool Scheduler::all_done() const {
    for (const auto& task : task_list_)
        if (!task.done) 
            return false;
    return true;
}

bool Scheduler::all_dead() const {
    for (const auto& robot : robot_list_)
        if (robot->get_state() != State::DEAD) 
            return false;
    return true;
}

void Scheduler::print_statistics() const {
    int done = 0;
    for (const auto& task : task_list_)
        if (task.done) done++;
    std::cout << "\n===== 模拟统计报告 =====\n";
    std::cout << "总耗时: " << time_ << " tick\n";
    std::cout << "任务完成率: " << done << "/" << task_list_.size()<< " (" << (task_list_.empty() ? 0 : done * 100 / task_list_.size()) << "%)\n";
    std::cout << "充电次数: " << charge_count_ << "\n";
    std::cout << "机器人死亡数: " << dead_count_ << "\n";
    std::cout << "========================\n";
}


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

void Scheduler::print_map_with_robot(const Map& map) const {
    for(int i = 0;i<map.row();i++){
        for(int j = 0;j<map.col();j++){
            bool is_robot_ = false;
            for(const auto& robot : robot_list_) {
                if(robot->x_pos() == i && robot->y_pos() == j) {
                    std::cout<<robot->get_id();
                    is_robot_ = true;
                }
            }
            if(!is_robot_) {
                std::cout<<map.get_cell(i, j);
            }
        }
        std::cout<<std::endl;
    }
}