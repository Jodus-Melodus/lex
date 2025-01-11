#pragma once
#include <string>

enum TokenType
{
	BinaryOperator,
	Integer,
	Float,
	String,
	LeftParenthesis,
	RightParenthesis,
	Identifier,
	Keyword,
	Assignment,
	Comma,
	Colon,
	Semicolon,
	LeftBrace,
	RightBrace,
	LeftBracket,
	RightBracket,
	Dot,
	Eof,
};

class Token
{
public:
	TokenType type;
	std::string value;
	int line;
	int column;
	Token(int line, int column, TokenType type, std::string value) : column(column), line(line), type(type), value(value) {};
	std::string toString() const;
	~Token() {};
};
