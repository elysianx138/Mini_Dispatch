#ifndef ROBOT_H
#define ROBOT_H

#include <tuple>
#include <vector>
#include "Map/map.h"
enum class State {Idle, Moving, Working, Charging, RETURNING};
struct BfsNode {
    int x_;
    int y_;
    int parent_;
};

struct Point {
    int x_;
    int y_;
};

std::string State_to_string(State state);
std::vector<std::tuple<int, int>> bfs(Map& map, int x, int y, int target_x, int target_y);
class Robot {
    int id_;
    int x_;
    int y_;
    int power_;
    std::vector<Point> path_;
    State state_;
    State check_state();
public:
    Robot(int id, int x, int y);
    int x_pos() const;
    int y_pos() const;
    int get_id() const;
    int get_power() const;
    void get_assign();
    std::tuple<int, int, int, int, State> get_msg() const;
    void moving();
};

#endif