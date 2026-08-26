#ifndef EXCEPT_H
#define EXCEPT_H

#include <stdexcept>
#include <string>
class Error : public std::runtime_error{
public:
    Error(const std::string& msg) : std::runtime_error(msg) {} ;
};

class Size_error : public Error{
public:
    Size_error(const std::string& size) : Error("地图尺寸错误, 请检查: " + size) {};
};

class File_error : public Error{
public:
    File_error(const std::string& path) : Error("文件路径错误, 请检查: " + path) {};
};

class Path_error : public Error{
public:
    Path_error(int x, int y) : Error("路径不可到达: "  + std::to_string(x) + " " + std::to_string(y)) {};
};

class Robot_error : public Error{
public:
    Robot_error(const std::string& msg, int id_) : Error("机器人错误" + std::to_string(id_) + ": " + msg) {};
};

#endif