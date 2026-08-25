#ifndef BFS_H
#define BFS_H
#include "Robot/robot.h"
#include "Map/map.h"
#include <vector>

struct BfsNode {
    int x_;
    int y_;
    int parent_;
};

std::vector<std::tuple<int, int>> recursion(const std::vector<BfsNode>& Node, int k, std::vector<std::tuple<int, int>>& ans);
std::vector<std::tuple<int, int>> bfs(Map& map, int x, int y, int target_x, int target_y);
#endif