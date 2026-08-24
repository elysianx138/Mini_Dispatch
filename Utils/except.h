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

#endif