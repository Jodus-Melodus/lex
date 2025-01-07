#pragma once
#include <string>
#include <deque>
#include "Token.h"

struct LexerResult
{
	std::deque<Token> tokens;
	std::string error;
};

class Lexer
{
public:
	Lexer(std::string sourceCode) : sourceCode(sourceCode) {};
	LexerResult tokenize();
	~Lexer() {};

private:
	std::string sourceCode;
};
