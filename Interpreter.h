#pragma once
#include <utility>
#include <iostream>
#include <string>
#include "Node.h"
#include "RuntimeValue.h"
#include "Error.h"

struct InterpreterResult
{
	RuntimeValue *value;
	Error error;
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
