#include "Map/map.h"
#include "Task/task.h"
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
    return 0;
}