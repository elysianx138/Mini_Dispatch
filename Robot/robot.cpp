#include "robot.h"
#include "Map/map.h"
#include "Utils/bfs.h"

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

std::tuple<int, int, int, int, State> Robot::get_msg() const {
    return std::make_tuple(id_, x_, y_, power_, state_);
}

void Robot::moving() {
    Point p = path_.front();
    int next_x = p.x_;
    int next_y = p.y_;

    x_ = next_x;
    y_ = next_y;
    power_ -= 10;
    path_.erase(path_.begin());
    state_ = State::Moving;
}