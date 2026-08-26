#ifndef ROBOT_H
#define ROBOT_H

#include <tuple>
#include <vector>
#include <memory>
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
    int loss_;
    int power_threshold_;
    std::vector<Point> path_;
    State state_;

    Task* target_task;
    Power target_power;

    
    void tell_power_threshold(Map& map);
    void finished_task();
    void turn_to_dead();
    void charging_and_finished_power();

    void decide_path(Map& map);
    void moving();
    Power decide_charge(Map& map);
    void arrived_task_pos();
    void arrived_power_pos();

public:
    Robot(int id, int x, int y);
    int x_pos() const;
    int y_pos() const;
    int get_id() const;
    int get_power() const;
    void step(Map& map);
    State get_state() const;
    void get_msg() const;
    void receive_task(Task* task, Map& map);
    
};

#endif