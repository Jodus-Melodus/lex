#pragma once
#include <string>

class Error
{
private:
    std::string message;
    int line;
    int column;
    bool empty;
    std::string generateErrorArrows();

public:
    Error(std::string message, int line, int column);
    Error();
    std::string toString();
    bool isEmpty();
    ~Error();
};