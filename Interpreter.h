#pragma once
#include <utility>
#include <iostream>
#include "Node.h"
#include "RuntimeValue.h"

class Interpreter
{
private:
	Node *ast;
	RuntimeValue* interpretBinaryExpression(BinaryExpression* node);

public:
	Interpreter(Node *ast) : ast(ast) {};
	RuntimeValue *interpret();
	RuntimeValue *interpretNode(Node *node);
	~Interpreter() {};
};
