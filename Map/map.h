#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>


class MAP {
    std::vector<std::vector<char>> grid_;
    int rows_;
    int cols_;
public:
    MAP(int rows, int cols);
    ~MAP();
    void Load_map_from_file(const std::string& path);
    void print_map();
};

#endif