#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <vector>
#include "Token.h"
#include "Error.h"

const std::string KEYWORDS[] = {std::string("let")};

struct LexerResult
{
	std::deque<Token> tokens;
	std::vector<Error> errors;
};

class Lexer
{
public:
	Lexer(std::string sourceCode) : sourceCode(sourceCode) {};
	LexerResult tokenize();
	~Lexer() {};

private:
	std::string sourceCode = "";
	std::deque<Token> tokens = {};
	std::vector<Error> errors = {};
	int line = 1;
	int column = 1;
	char peek();
	char eat();
	void processNames();
	void processNumbers();
	void processStrings();
};
