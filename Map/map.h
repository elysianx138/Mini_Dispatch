#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Task/task.h"

class Map {
    std::vector<std::vector<char>> grid_;
    int rows_;  // ÐÐ
    int cols_;  // ÁÐ
public:
    Map(int rows, int cols);
    void Load_map_from_file(const std::string& path);
    void print_map();
    int row() const { return rows_; }
    int col() const { return cols_; }
    std::vector<Task> get_task_list();
    bool is_walkable(int x, int y);
};

#endif