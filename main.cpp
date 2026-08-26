#include "Map/map.h"
#include "Task/task.h"
#include "Robot/robot.h"
#include "Utils/bfs.h"
#include "Scheduler/scheduler.h"
#include <iostream>

int main() {
    Map map(10, 30);
    try{
        map.Load_map_from_file("Map/map.txt");
    } catch (std::exception& e) {
        std::cout<<e.what()<<std::endl;
    }
    map.print_map();
    std::vector<std::unique_ptr<Robot>> robot_list;
    robot_list.push_back(std::make_unique<Robot>(1, 1, 1));
    robot_list.push_back(std::make_unique<Robot>(1, 1, 10));
    std::vector<Task> task_list = map.get_task_list();
    Scheduler scheduler(task_list, robot_list);


    scheduler.step(map);
    scheduler.print_all_robot_msg();
    scheduler.step(map);
    scheduler.print_all_robot_msg();
    
    return 0;
}