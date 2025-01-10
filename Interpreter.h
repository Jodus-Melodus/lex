#pragma once
#include <utility>
#include <iostream>
#include <string>
#include "Node.h"
#include "RuntimeValue.h"

struct InterpreterResult
{
	RuntimeValue *value;
	std::string error;
};

class Interpreter
{
private:
	Node *ast;
	InterpreterResult interpretBinaryExpression(BinaryExpression *node);

public:
	Interpreter(Node *ast) : ast(ast) {};
	InterpreterResult interpret();
	InterpreterResult interpretNode(Node *node);
	~Interpreter() {};
};
