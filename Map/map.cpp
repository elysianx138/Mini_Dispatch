#include "map.h"
#include "Utils/except.h"
Map::Map(int rows, int cols) : rows_(rows), cols_(cols), grid_(rows, std::vector<char>(cols)) {}
Map::Map() : rows_(0), cols_(0) {};
void Map::Load_map_from_file(const std::string& path, Map& map) {
    std::ifstream in(path);
        if(!(in.is_open()))
            throw File_error(path);
        
        std::string line;
        int temp_rows = 0;
        int temp_cols = 0;
        while(std::getline(in, line)){
            if(temp_rows == 0)
                temp_cols = line.size();
            temp_rows++;
        }
        
            in.clear();
            in.seekg(0);

        map.rows_ = temp_rows;
        map.cols_ = temp_cols;
        map.grid_ = std::vector<std::vector<char>>(map.rows_, std::vector<char>(map.cols_));
        for(int i = 0; i< map.rows_;i++){
            std::getline(in, line);
            for(int j = 0;j<map.cols_;j++){
                map.grid_[i][j] = line[j];
            }
        }
}

void Map::print_map() {
    for(int i = 0; i < rows_; i++) {
        for(int j = 0; j < cols_; j++) {
            std::cout << grid_[i][j];
        }
        std::cout << std::endl;
    }
}

bool Map::is_walkable(int x, int y) {
    if(x<0||x>=rows_||y<0||y>=cols_)
        return false;
    if(grid_[x][y] == '#')
        return false;
    return true;
}

std::vector<Task> Map::get_task_list() {
    std::vector<Task> pos;
    for(int i = 0;i<rows_;i++){
        for(int j = 0;j<cols_;j++){
            if(grid_[i][j] == 'T')
                pos.push_back(Task(i, j));
        }
    }
    return pos;
}

std::vector<Power> Map::get_power_list() {
    std::vector<Power> pos;
    for(int i = 0;i<rows_;i++){
        for(int j = 0;j<cols_;j++){
            if(grid_[i][j] == 'C')
                pos.push_back(Power(i, j));
        }
    }
    return pos;
}

char Map::get_cell(int i, int j) const {
    return grid_[i][j];
}


