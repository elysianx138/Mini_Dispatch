#include "Map/map.h"
#include "Task/task.h"
#include "Robot/robot.h"
#include "Utils/bfs.h"
#include <iostream>

int main() {
    Map map(10, 30);
    try{
        map.Load_map_from_file("Map/map.txt");
    } catch (std::exception& e) {
        std::cout<<e.what()<<std::endl;
    }
    
    map.print_map();
    std::cout<<map.is_walkable(1, 1)<<' '<<map.is_walkable(11, 2)<<std::endl;
    std::vector<std::tuple<int, int>> v = map.get_task_pos();
    for(const auto x : v) {
        struct Task task_1(std::get<0>(x), std::get<1>(x), Priority::LOW);
        task_1.check_station();
    }
    Robot robot_1 (1, 1, 1);
    robot_1.get_msg();
    
    auto bfs_path = bfs(map, robot_1.x_pos(), robot_1.y_pos(), std::get<0>(v[0]), std::get<1>(v[0]));
    for(const auto x : bfs_path) {
        std::cout<<x.x_<<" "<<x.y_<<std::endl;
    }
    robot_1.decide_path(std::get<0>(v[0]), std::get<1>(v[0]), map);
    robot_1.moving();
    robot_1.moving();
    robot_1.get_msg();
    return 0;
}