#ifndef ROBOT_H
#define ROBOT_H

#include <tuple>
#include <vector>
#include "Map/map.h"
#include "Utils/point.h"
enum class State {Idle, Moving, Working, Charging, RETURNING};


std::string State_to_string(State state);

class Robot {
    int id_;
    int x_;
    int y_;
    int power_;
    std::vector<Point> path_;
    State state_;

public:
    Robot(int id, int x, int y);
    int x_pos() const;
    int y_pos() const;
    int get_id() const;
    int get_power() const;
    void decide_path(int target_x, int target_y, Map& map);
    void get_msg() const;
    void moving();
};

#endif