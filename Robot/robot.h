#ifndef ROBOT_H
#define ROBOT_H

#include <tuple>
#include <vector>
enum class State {Idle, Moving, Working, Charging};
struct BfsNode {
    int x_;
    int y_;
    int parent_;
};
std::string State_to_string(State state);

class Robot {
    int id_;
    int x_;
    int y_;
    int power_;
    std::vector<std::tuple<int, int>> path_;
    State state_;
public:
    Robot(int id, int x, int y, int power);
    int x_pos() const;
    int y_pos() const;
    int get_id() const;
    int get_power() const;
    void get_assign();
    std::tuple<int, int, int, int, State> get_state() const;
    void move();
};

#endif