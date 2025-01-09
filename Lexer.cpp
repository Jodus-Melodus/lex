#include "Lexer.h"

LexerResult Lexer::tokenize()
{
	while (!this->sourceCode.empty())
	{
		char c = this->peek();

		switch (c)
		{
		case ' ':
		case '\t':
		case '\n':
		case '\r':
			this->eat();
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
			this->tokens.push_back(Token(this->line, this->column, TokenType::BinaryOperator, std::string(1, this->eat())));
			break;
		case '(':
			this->tokens.push_back(Token(this->line, this->column, TokenType::LeftParenthesis, "("));
			break;
		case ')':
			this->tokens.push_back(Token(this->line, this->column, TokenType::RightParenthesis, ")"));
			break;
		case '[':
			this->tokens.push_back(Token(this->line, this->column, TokenType::LeftBracket, "["));
			break;
		case ']':
			this->tokens.push_back(Token(this->line, this->column, TokenType::RightBracket, "]"));
			break;
		case '{':
			this->tokens.push_back(Token(this->line, this->column, TokenType::LeftBrace, "{"));
			break;
		case '}':
			this->tokens.push_back(Token(this->line, this->column, TokenType::RightBrace, "}"));
			break;
		case '"':
			this->processStrings();
			break;
		default:
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
			{
				this->processNames();
			}
			else if (c >= '0' && c <= '9')
			{
				this->processNumbers();
			}
			else
			{
				this->errors.push_back(std::string("Syntax Error: Unknown character"));
			}
		}
	}

	this->tokens.push_back(Token(this->line, this->column, TokenType::Eof, ""));

	return {this->tokens, this->errors};
}

char Lexer::peek()
{
	return this->sourceCode[0];
}

char Lexer::eat()
{
	char c = this->peek();
	this->sourceCode.erase(0, 1);
	return c;
}

void Lexer::processNames()
{
	std::string name = "";

	while (!this->sourceCode.empty())
	{
		char character = this->peek();
		if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || character == '_')
		{
			name += character;
		}
		else
		{
			break;
		}
		this->eat();
	}

	if (name == "int" || name == "float")
	{
		this->tokens.push_back(Token(this->line, this->column, TokenType::Keyword, name));
	}
	else
	{
		this->tokens.push_back(Token(this->line, this->column, TokenType::Identifier, name));
	}
}

void Lexer::processNumbers()
{
	std::string number = "";
	bool decimal = false;

	while (!this->sourceCode.empty())
	{
		char character = this->peek();

		if (character >= '0' && character <= '9')
		{
			number += character;
		}
		else if (character == '.')
		{
			if (decimal)
			{
				this->errors.push_back(std::string("Syntax Error: Found two '.', numbers can only contain one decimal point."));
			}
			number += character;
			decimal = true;
		}
		else
		{
			break;
		}
		this->eat();
	}

	if (decimal)
	{
		this->tokens.push_back(Token(this->line, this->column, TokenType::Float, number));
	}
	else
	{
		this->tokens.push_back(Token(this->line, this->column, TokenType::Integer, number));
	}
}

void Lexer::processStrings()
{
	this->eat();
	std::string value = "";

	while (this->peek() != '"')
	{
		value += this->eat();
	}

	this->eat();
	this->tokens.push_back(Token(this->line, this->column, TokenType::String, value));
}
