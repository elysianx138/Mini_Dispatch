#include <algorithm>
#include <queue>
#include "bfs.h"
std::vector<Point> recursion(const std::vector<BfsNode>& Node, int k, std::vector<Point>& ans) {
    if(Node[k].parent_ == -1) {
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
        
    ans.push_back(Point{Node[k].x_, Node[k].y_});
    return recursion(Node, Node[k].parent_, ans);
}
std::vector<Point> bfs(Map& map, int x, int y, int target_x, int target_y) {
    int dx[5] = {0, 0, 1, 0, -1};
    int dy[5] = {0, 1, 0, -1, 0};

    std::queue<std::tuple<int, int>> q;
    std::vector<BfsNode> Node;
    std::vector<Point> ans;
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