#ifndef ROBOT_H
#define ROBOT_H

#include <tuple>
#include <vector>
#include "Map/map.h"
#include "Task/task.h"
#include "Utils/point.h"
enum class State {Idle, Moving, Working, Charging, RETURNING, DEAD};


std::string State_to_string(State state);

class Robot {
    int id_;
    int x_;
    int y_;
    int power_;
    std::vector<Point> path_;
    State state_;

    void state_machine();

public:
    Robot(int id, int x, int y);
    int x_pos() const;
    int y_pos() const;
    int get_id() const;
    int get_power() const;
    void decide_path(Task assigned_task, Map& map);
    State get_state() const;
    void moving();
    void get_msg() const;
    void finished_task(Task& task);
};

#endif