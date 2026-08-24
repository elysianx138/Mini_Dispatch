#include "Map/map.h"
#include <iostream>

int main() {
    MAP map(10, 30);
    try{
        map.Load_map_from_file("Map/map.txt");
    } catch (std::exception& e) {
        std::cout<<e.what()<<std::endl;
    }
    
    map.print_map();

    return 0;
}