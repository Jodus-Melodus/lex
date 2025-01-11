#pragma once
#include <vector>
#include "Token.h"
#include "Node.h"
#include "Error.h"

struct ParserResult
{
	Node *node;
	std::vector<Error> errors;
};

class Parser
{
public:
	Parser(std::deque<Token> tokens) : tokens(tokens) {};
	ParserResult parse();
	~Parser() {};

private:
	std::deque<Token> tokens;
	std::deque<Node *> nodes;
	std::vector<Error> errors;
	Token *peek();
	Token *eat();
	ParserResult parseStatement();
	ParserResult parseExpression();
	ParserResult parseAdditiveExpression();
	ParserResult parseMultiplicativeExpression();
	ParserResult parsePrimaryExpression();
};
