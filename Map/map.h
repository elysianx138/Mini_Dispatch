#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Task/task.h"
#include "Power/power.h"

class Map {
    std::vector<std::vector<char>> grid_;
    int rows_;  // ÐÐ
    int cols_;  // ÁÐ
public:
    Map (int rows, int cols);
    Map ();
    static void Load_map_from_file(const std::string& path, Map& map);
    void print_map();
    int row() const { return rows_; }
    int col() const { return cols_; }
    std::vector<Task> get_task_list();
    std::vector<Power> get_power_list();
    bool is_walkable(int x, int y);
    char get_cell(int i, int j) const ;
};

#endif