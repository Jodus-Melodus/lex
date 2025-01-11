#pragma once
#include <deque>
#include <string>
#include "Node.h"

class Node
{
public:
    Node() {}
    virtual std::string toString() = 0;
    virtual ~Node() {}
};

class Scope : public Node
{
public:
    std::deque<Node *> body;
    Scope(std::deque<Node *> body) : body(body) {}
    std::string toString() override
    {
        std::string result = "{ \"type\" : \"scope\", \"body\" : [";
        for (size_t i = 0; i < body.size(); ++i)
        {
            result += body[i]->toString();
            if (i != body.size() - 1)
            {
                result += ", ";
            }
        }
        result += "]}";
        return result;
    }
    ~Scope() {}
};

class BinaryExpression : public Node
{
public:
    Node *left;
    Node *right;
    char op;
    BinaryExpression(Node *left, Node *right, char op) : left(left), right(right), op(op) {}
    std::string toString() override
    {
        return "{ \"type\" : \"binary expression\", \"left\" : " + left->toString() + ", \"operand\" : \"" + op + "\", \"right\" : " + right->toString() + " }";
    }
    ~BinaryExpression() {}
};

class FloatLiteral : public Node
{
public:
    float value;
    FloatLiteral(float value) : value(value) {}
    std::string toString() override
    {
        return "{ \"type\" : \"float literal\", \"value\" : " + std::to_string(value) + " }";
    }
    ~FloatLiteral() {}
};

class IdentifierLiteral : public Node
{
public:
    std::string value;
    IdentifierLiteral(std::string value) : value(value) {}
    std::string toString() override
    {
        return "{ \"type\" : \"identifier literal\", \"value\" : \"" + value + "\" }";
    }
    ~IdentifierLiteral() {}
};

class IntegerLiteral : public Node
{
public:
    int value;
    IntegerLiteral(int value) : value(value) {}
    std::string toString() override
    {
        return "{ \"type\" : \"integer literal\", \"value\" : " + std::to_string(value) + " }";
    }
    ~IntegerLiteral() {}
};

class NullLiteral : public Node
{
public:
    NullLiteral() {};
    std::string toString() { return "{ \"type\" : \"null literal\"}"; };
    ~NullLiteral() {};
};

class StringLiteral : public Node
{
public:
    std::string value;
    StringLiteral(std::string value) : value(value) {}
    std::string toString() override
    {
        return "{ \"type\" : \"string literal\", \"value\" : \"" + value + "\" }";
    }
    ~StringLiteral() {}
};
