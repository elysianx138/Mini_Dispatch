#include "Map/map.h"
#include "Task/task.h"
#include "Robot/robot.h"
#include "Utils/bfs.h"
#include "Scheduler/scheduler.h"
#include <iostream>
#include <windows.h>

int main() {
    srand(time(0));
    Map map;
    try{
        Map::Load_map_from_file("Map/map.txt", map);
    } catch (std::exception& e) {
        std::cout<<e.what()<<std::endl;
    }
    map.print_map();
    std::vector<std::unique_ptr<Robot>> robot_list;
    robot_list.push_back(std::make_unique<Robot>(1, 1, 1));
    robot_list.push_back(std::make_unique<Robot>(2, 1, 10));
    std::vector<Task> task_list = map.get_task_list();
    std::unique_ptr<Scheduler> scheduler = nullptr;
    try{
        scheduler = std::make_unique<Scheduler>(task_list, robot_list, map);
    } catch (std::exception& e){
        std::cout<<e.what()<<std::endl;
    }
    

    for(int i = 1;i<=20;i++){
        try{
            scheduler->step(map);
        } catch (std::exception& e){
            std::cout<<e.what()<<std::endl;
        }
        scheduler->print_map_with_robot(map);
        scheduler->print_all_robot_msg();
        scheduler->print_all_task_msg();
        Sleep(1000);
    }
    
    
    return 0;
}

// while循环
// 系统状态显示