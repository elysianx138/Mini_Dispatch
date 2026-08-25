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
        case State::RETURNING: return "returning";
    }
    return "Unknown";
}

Robot::Robot(int id, int x, int y) : id_(id), x_(x), y_(y), power_(100), state_(State::Idle) {}

int Robot::x_pos() const { return x_; }
int Robot::y_pos() const { return y_; }
int Robot::get_id() const { return id_;}
int Robot::get_power() const { return power_; }

void Robot::get_msg() const {
    std::cout<<"机器人ID: "<<id_<<" 机器人坐标x: "<<x_<<" 机器人坐标y: "<<y_<<" 机器人电量: "<<power_<<" 机器人状态: "<<State_to_string(state_)<<std::endl;
}

void Robot::decide_path(int target_x, int target_y, Map& map) {
    std::vector<Point> ans = bfs(map, x_, y_, target_x, target_y);
    if(ans.empty())
        throw Path_error(target_x, target_y);
    path_ = ans;
}

void Robot::moving() {
    if(path_.empty())
        return;
    Point p = path_.front();
    int next_x = p.x_;
    int next_y = p.y_;

    x_ = next_x;
    y_ = next_y;
    power_ -= 10;
    path_.erase(path_.begin());
    state_ = State::Moving;
}