#ifndef BFS_H
#define BFS_H
#include "Map/map.h"
#include "Utils/point.h"
#include <vector>

struct BfsNode {
    int x_;
    int y_;
    int parent_;
};

std::vector<Point> recursion(const std::vector<BfsNode>& Node, int k, std::vector<Point>& ans);
std::vector<Point> bfs(Map& map, int x, int y, int target_x, int target_y);
#endif