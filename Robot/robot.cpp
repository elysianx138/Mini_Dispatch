#include "robot.h"
#include "Map/map.h"
#include <queue>
#include <algorithm>
class Robot;
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

std::vector<std::tuple<int, int>> recursion(const std::vector<BfsNode>& Node, int k, std::vector<std::tuple<int, int>>& ans) {
    if(Node[k].parent_ == -1) {
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
        
    ans.push_back(std::make_tuple(Node[k].x_, Node[k].y_));
    return recursion(Node, Node[k].parent_, ans);
}
std::vector<std::tuple<int, int>> bfs(Map& map, int x, int y, int target_x, int target_y) {
    int dx[5] = {0, 0, 1, 0, -1};
    int dy[5] = {0, 1, 0, -1, 0};

    std::queue<std::tuple<int, int>> q;
    std::vector<BfsNode> Node;
    std::vector<std::tuple<int, int>> ans;
    std::vector<std::vector<bool>> visited(map.row(), std::vector<bool>(map.col(), false));
    visited[x][y] = true;
    int k = -1;
    q.push(std::make_tuple(x, y));
    Node.push_back({x, y, k});

    while(!q.empty()) {
        auto cur = q.front();
        int cur_x = std::get<0>(cur);
        int cur_y = std::get<1>(cur);
        q.pop();

        k++;

        if(cur_x == target_x && cur_y == target_y) {
            return recursion(Node, k, ans);
        }

        for(int i = 1;i<=4;i++){
            int next_x = cur_x + dx[i];
            int next_y = cur_y + dy[i];
            if(map.is_walkable(next_x, next_y) && !visited[next_x][next_y]) {
                visited[next_x][next_y] = true;
                q.push(std::make_tuple(next_x, next_y));
                Node.push_back({next_x, next_y, k});
            }
        }
    }
    return ans;
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