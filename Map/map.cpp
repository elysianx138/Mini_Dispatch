#include "map.h"
#include "Utils/except.h"
Map::Map(int rows, int cols) : rows_(rows), cols_(cols) {
    grid_.resize(rows);
    for(int i = 0; i < rows; i++) {
        grid_[i].resize(cols);
    }
}

void Map::Load_map_from_file(const std::string& path) {
    std::ifstream in(path);
        if(!(in.is_open()))
            throw File_error(path);
        
        std::string line;
        int temp_rows = 0;
        while(std::getline(in, line)){
            temp_rows++;
        }
            in.clear();
            in.seekg(0);
        if(temp_rows > rows_)
            throw Size_error(std::to_string(rows_));

        for(int i = 0; i< temp_rows;i++){
            std::getline(in, line);
            int temp_cols = line.size();
            if(temp_cols > cols_)
                throw Size_error(std::to_string(cols_));
            for(int j = 0;j<temp_cols;j++){
                grid_[i][j] = line[j];
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

std::vector<std::tuple<int, int>> Map::get_task_pos() {
    std::vector<std::tuple<int, int>> pos;
    for(int i = 0;i<rows_;i++){
        for(int j = 0;j<cols_;j++){
            if(grid_[i][j] == 'T')
                pos.push_back(std::make_tuple(i, j));
        }
    }
    return pos;
}


