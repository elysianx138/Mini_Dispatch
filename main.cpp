#include "Map/map.h"
#include "Task/task.h"
#include "Robot/robot.h"
#include "Utils/bfs.h"
#include "Utils/logger.h"
#include "Scheduler/scheduler.h"
#include <iostream>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#endif

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

    log_event(0, "INFO", "模拟开始: " + std::to_string(robot_list.size()) +
              " 个机器人, " + std::to_string(task_list.size()) + " 个任务");

    std::unique_ptr<Scheduler> scheduler = nullptr;
    try{
        scheduler = std::make_unique<Scheduler>(task_list, robot_list, map);
    } catch (std::exception& e){
        std::cout<<e.what()<<std::endl;
        return 1;
    }

    while (!scheduler->all_done() && !scheduler->all_dead()) {
        try{
            scheduler->step(map);
        } catch (std::exception& e){
            std::cout<<e.what()<<std::endl;
        }
        scheduler->print_map_with_robot(map);
        scheduler->print_all_robot_msg();
        scheduler->print_all_task_msg();
#ifdef _WIN32
        Sleep(1000);
#else
        std::this_thread::sleep_for(std::chrono::seconds(1));
#endif
        
    }

    scheduler->print_statistics();
    return 0;
}
