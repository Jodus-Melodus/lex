#pragma once
#include <vector>
#include "Token.h"
#include "Node.h"

struct ParserResult
{
	Node *node;
	std::vector<std::string> errors;
};

class Parser
{
public:
	Parser(std::deque<Token> tokens) : tokens(tokens) {};
	ParserResult parse();
	~Parser() {};

private:
	std::deque<Token> tokens;
	Token *peek();
	Token *eat();
	ParserResult parseStatement();
	ParserResult parseExpression();
	ParserResult parseAdditiveExpression();
	ParserResult parseMultiplicativeExpression();
	ParserResult parsePrimaryExpression();
};
