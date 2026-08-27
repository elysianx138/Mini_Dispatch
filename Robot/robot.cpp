#include "robot.h"
#include "Map/map.h"
#include "Utils/bfs.h"
#include "Utils/except.h"
std::string State_to_string(State state) {
    switch(state) {
        case State::Idle: return "Idle";
        case State::Moving: return "Moving";
        case State::Working: return "Working";
        case State::Charging: return "Charging";
        case State::RETURNING: return "Returning";
        case State::DEAD: return "Dead";
    }
    return "Unknown";
}

Robot::Robot(int id, int x, int y) : id_(id), x_(x), y_(y), power_(100), state_(State::Idle), loss_(5), power_threshold_(60), target_task(nullptr) {}

int Robot::x_pos() const { return x_; }
int Robot::y_pos() const { return y_; }
int Robot::get_id() const { return id_;}
int Robot::get_power() const { return power_; }
State Robot::get_state() const { return state_; }
void Robot::get_msg() const {
    std::cout<<"机器人ID: "<<id_<<" 机器人坐标x: "<<x_<<" 机器人坐标y: "<<y_<<" 机器人电量: "<<power_<<" 机器人状态: "<<State_to_string(state_)<<std::endl;
}
void Robot::receive_task(Task* task, Map& map) {
    target_task = task;
    decide_path(map);
}

void Robot::step(Map& map) {
    switch(state_) {
        case State::DEAD:
        // 机器人处于待机死亡状态
            break;
        case State::Idle:
        // 等待任务, 可领取任务
            break;
        case State::Charging:
        // 机器人正在充电: 是否充满?
            charging_and_finished_power();
            break;
        case State::Working:
            finished_task();
            break;
        // 机器人正在工作: 是否完成任务?
        case State::Moving:
        // 机器人移动: 是否到达目的地?/是否电量低于阈值?/没电?/继续移动
            moving();
            tell_power_threshold(map);
            arrived_task_pos();
            turn_to_dead();
            break;

        case State::RETURNING:
            moving();
            arrived_power_pos();
            turn_to_dead();
            break;
        // 返回充电: 是否到达目的地?/是否没电? 同时放弃任务;//继续移动
    }
}

//  领取任务 -> 思考路径 
// 什么时候判断状态机? -> 工作?如果工作证明电量已经满足且不需要规划 / 死亡? 死亡就是待机,没必要 / 充电? 没必要/ 待机? 如果要么工作完成/要么无法完成,可以领取任务进行状态机
//  状态:完成任务? / 判断是否完成任务/ /是否需要充电 / 是否没电 /  
//  完成工作->自动充电(没电? 不能动,待机) -> 没充电的 ->BFS寻路径 -> 最优解(无机器人充电)
// 不能完成任务->向上放弃任务(调度器再分配?) -> 再次被分配呢?
//  需要充电, 优先级最高, 充满电 -> 完成任务

void Robot::decide_path(Map& map) {
    int target_x = target_task->x_;
    int target_y = target_task->y_;
    std::vector<Point> ans = bfs(map, x_, y_, target_x, target_y);
    if(ans.empty())
        throw Path_error(target_x, target_y);
    path_ = ans;
    state_ = State::Moving;
}

void Robot::turn_to_dead() {
    if(power_ <= 0){
        power_ = 0;
        state_ = State::DEAD;
    }
        
}

void Robot::moving() {
    if(path_.empty())
        return;
    Point p = path_.front();
    int next_x = p.x_;
    int next_y = p.y_;
    x_ = next_x;
    y_ = next_y;
    power_ -= loss_;
    path_.erase(path_.begin());
    if(state_ != State::RETURNING)
        state_ = State::Moving;
}

void Robot::tell_power_threshold(Map& map) {
    if(power_ <= power_threshold_){
        state_ = State::RETURNING;
        target_task->assigned = false;
        target_task = nullptr;
        target_power = decide_charge(map);
    }
        
}
Power Robot::decide_charge(Map& map) {
    std::vector<Power> power_list = map.get_power_list();
    int min = -1;
    Power power_ans;
    for(const auto& power : power_list) {
        int target_x = power.x_;
        int target_y = power.y_;

        std::vector<Point> ans = bfs(map, x_, y_, target_x, target_y);
        if(ans.empty())
            throw Path_error(target_x, target_y);
        if(min>ans.size() || min == -1){
            path_ = ans;
            power_ans = power;
            min = ans.size();
        }
    }
    state_ = State::RETURNING;
    return power_ans;
}


void Robot::arrived_task_pos() {
    if(target_task == nullptr)
        return;
    int target_x = target_task->x_;
    int target_y = target_task->y_;
    if(target_x == x_ && target_y == y_) {
        state_ = State::Working;
        finished_task();
    }
}

void Robot::arrived_power_pos() {
    int target_x = target_power.x_;
    int target_y = target_power.y_;
    if(target_x == x_ && target_y == y_) {
        state_ = State::Charging;
        charging_and_finished_power();
    }
}

void Robot::finished_task() {
    target_task->required_power_ -= 10;
    if(target_task->required_power_ <=0) {
        target_task->required_power_  = 0;
        target_task->done = true;
        state_ = State::Idle;
    }
}

void Robot::charging_and_finished_power() {
    power_+=10;
    if(power_>=100) {
        power_ = 100;
        state_ = State::Idle;
    }
}