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
    std::vector<std::tuple<int, int>> v = map.get_pos();
    for(const auto x : v) {
        struct Task task_1(std::get<0>(x), std::get<1>(x), Priority::LOW);
        task_1.check_station();
    }
    Robot robot_1 (1, 1, 1);
    auto state = robot_1.get_msg();
    std::cout<<"机器人ID: "<<std::get<0>(state)<<" 机器人坐标x: "<<std::get<1>(state)<<" 机器人坐标y: "<<std::get<2>(state)<<" 机器人电量: "<<std::get<3>(state)<<" 机器人状态: "<<State_to_string(std::get<4>(state))<<std::endl;
    auto bfs_path = bfs(map, std::get<1>(state), std::get<2>(state), std::get<0>(v[0]), std::get<1>(v[0]));
    for(const auto x : bfs_path) {
        std::cout<<std::get<0>(x)<<" "<<std::get<1>(x)<<std::endl;
    }
    return 0;
}