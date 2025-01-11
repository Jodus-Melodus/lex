#include "Error.h"

std::string Error::generateErrorArrows()
{
    std::string arrows = "";

    for (int i = 0; i < this->column; i++)
    {
        arrows += ' ';
    }
    arrows += "^\n";

    return arrows;
}

Error::Error(std::string message, int line, int column)
    : message(message), line(line), column(column), empty(false)
{
}

Error::Error()
    : message(""), line(0), column(0), empty(true)
{
}

std::string Error::toString()
{
    if (this->empty)
    {
        return "";
    }
    else
    {
        std::string result = this->generateErrorArrows();
        result += this->message;
        result += " in line " + std::to_string(this->line) + " column " + std::to_string(this->column);

        return result;
    }
}

bool Error::isEmpty()
{
    return this->empty;
}

Error::~Error()
{
}