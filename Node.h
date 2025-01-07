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
        std::string result = "{\n";
        for (Node *node : body)
        {
            result += node->toString() + "\n";
        }
        result += "}";
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
    std::string toString() { return "BinaryExpression(" + left->toString() + " " + op + " " + right->toString() + ")"; }
    ~BinaryExpression() {}
};

class FloatLiteral : public Node
{
public:
    float value;
    FloatLiteral(float value) : value(value) {}
    std::string toString() override
    {
        return std::to_string(value);
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
        return value;
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
        return std::to_string(value);
    }
    ~IntegerLiteral() {}
};

class NullLiteral : public Node
{
public:
    NullLiteral() {};
    std::string toString() { return std::string(""); };
    ~NullLiteral() {};
};

class StringLiteral : public Node
{
public:
    std::string value;
    StringLiteral(std::string value) : value(value) {}
    std::string toString() override
    {
        return value;
    }
    ~StringLiteral() {}
};
