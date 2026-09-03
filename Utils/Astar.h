#ifndef ASTAR_H
#define ASTAR_H
#include "Map/map.h"
#include <queue>
#include <vector>
#include "Utils/point.h"
#include <cmath>
#include <algorithm>
struct AStarNode {
    int x_;
    int y_;
    int g_;
    int f_;
    int come_from_;
    int idx_;

    AStarNode(int x, int y);
    AStarNode(int x, int y, int g, int come_from, int idx);
};

struct Cmp {
    const bool operator()(const AStarNode& a, const AStarNode& b) {
        return a.f_ > b.f_;
    }
};

std::vector<Point> a_star(Map& map, int x, int y, int target_x, int target_y);
std::vector<Point> recursion(const std::vector<AStarNode>& Node, int k, std::vector<Point>& ans);
int manhattan(int x, int y, int target_x, int target_y);

#endif