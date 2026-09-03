#include "Astar.h"

std::vector<Point> recursion(const std::vector<AStarNode>& Node, int k, std::vector<Point>& ans) {
    if(Node[k].come_from_ == -1) {
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
    ans.push_back(Point{Node[k].x_, Node[k].y_});
    return recursion(Node, Node[k].come_from_, ans);
}

int manhattan(int x, int y, int target_x, int target_y) {
    return std::abs(x - target_x) + std::abs(y - target_y); 
}

AStarNode::AStarNode(int x, int y) : x_(x), y_(y), g_(0) {
    come_from_ = -1;
    idx_ = 0;
};
AStarNode::AStarNode(int x, int y, int g, int come_from, int idx) : x_(x), y_(y), g_(g), come_from_(come_from), idx_(idx) {};

std::vector<Point> a_star(Map& map, int x, int y, int target_x, int target_y) {
    int dx[5] = {0, 0, 1, 0, -1};
    int dy[5] = {0, 1, 0, -1, 0};

    std::priority_queue<AStarNode, std::vector<AStarNode>, Cmp> frontier;
    std::vector<AStarNode> Node;
    std::vector<Point> ans;
    std::vector<std::vector<int>> cost_so_far(map.row(), std::vector<int>(map.col(), -1));
    AStarNode start(x, y);
    start.f_ = start.g_ + manhattan(x, y, target_x, target_y);
    frontier.push(start);
    Node.push_back(start);
    cost_so_far[x][y] = 0;   // 起点的最优 g = 0（否则绕回起点会被当成新格子反复入队）

    while(!(frontier.empty())) {
        AStarNode cur = frontier.top();
        frontier.pop();

        if(cur.g_ != cost_so_far[cur.x_][cur.y_]) continue;
            // 优化点 // 当长路径被替换时, frontier队列可能存在长路径, 后续可能会继续弹出剩余路径, 造成不必要的浪费

        if(cur.x_ == target_x && cur.y_ == target_y) {
            return recursion(Node,cur.idx_, ans);
        }

        for(int i = 1;i<=4;i++) {
            int next_x = cur.x_ + dx[i];
            int next_y = cur.y_ + dy[i];
            int next_g_ = cur.g_ + 1; // +1 : 计算出发点到下一点的代价 :: 后续抽象为函数

            if(!map.is_walkable(next_x, next_y)) continue;

            if(cost_so_far[next_x][next_y] == -1 || next_g_ < cost_so_far[next_x][next_y]) {
                // 理解点
                cost_so_far[next_x][next_y] = next_g_;
                
                int next_come_from_ = cur.idx_;
                int next_f_ = next_g_ + manhattan(next_x, next_y, target_x, target_y);
                int next_idx_ = Node.size();

                AStarNode next(next_x, next_y, next_g_, next_come_from_, next_idx_);
                next.f_ = next_f_;

                Node.push_back(next); // 理解点
                frontier.push(next);
            } else {
                continue;
            }
        }
    }
    return ans;
}