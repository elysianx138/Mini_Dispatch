#include "task.h"

std::string Priority_to_string(Priority priority) {
    switch (priority) {
        case Priority::LOW:
            return "LOW";
        case Priority::MEDIUM:
            return "MEDIUM";
        case Priority::HIGH:
            return "HIGH";
    }
    return "UNKNOWN";
}
Task::Task(int x, int y) : x_(x), y_(y), done(false), assigned(false) {
    srand(time(0));
    int r = rand()%3;
    type_ = Priority(r); 
};
Task::Task() {};
Task::Task(int x, int y, const Priority& type) : x_(x), y_(y), done(false), type_(type), assigned(false) {};
void Task::check_station() {
    std::string priority = Priority_to_string(type_);
    if(!done)
        std::cout<<"[ "<<priority<<" ] "<<x_<<" "<<y_<<"的状态为: "<<"未完成"<<std::endl;
    else
        std::cout<<"[ "<<priority<<" ] "<<x_<<" "<<y_<<"的状态为: "<<"已完成"<<std::endl;
}