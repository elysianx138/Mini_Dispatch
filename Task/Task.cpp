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
Task::Task(int x, int y) : x_(x), y_(y), done(false), assigned(false),required_power_(30) {
    int r = rand()%3;
    type_ = Priority(r); 
};
Task::Task() {};
Task::Task(int x, int y, const Priority& type) : x_(x), y_(y), done(false), type_(type), assigned(false), required_power_(30) {};
