#include "Lexer.h"

LexerResult Lexer::tokenize()
{
	std::deque<Token> tokens;
	std::string error = "";
	std::string name = "";
	std::string number = "";
	bool parsingNumber = false;
	bool parsingComment = false;
	int line = 1;
	int column = 1;

	for (char c : this->sourceCode)
	{
		if (parsingComment)
		{
			if (c == '#')
			{
				parsingComment = false;
			}
			continue;
		}

		if (!std::isalnum(c) && c != '.')
		{
			if (!name.empty())
			{
				if (name == "int" || name == "float")
				{
					tokens.push_back(Token(line, column, TokenType::Keyword, name));
				}
				else
				{
					tokens.push_back(Token(line, column, TokenType::Identifier, name));
				}
				name = "";
			}

			if (!number.empty())
			{
				if (number.find('.') != std::string::npos)
				{ // if contains '.' then it is a float
					tokens.push_back(Token(line, column, TokenType::Float, number));
				}
				else
				{
					tokens.push_back(Token(line, column, TokenType::Integer, number));
				}
				number = "";
				parsingNumber = false;
			}
		}

		switch (c)
		{
		case '\t':
		case ' ':
			continue;
		case '\n':
		case '\r':
			line++;
			column = 1;
			break;
		case '#':
			parsingComment = true;
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			tokens.push_back(Token(line, column, TokenType::BinaryOperator, std::string(1, c)));
			break;
		case '(':
			tokens.push_back(Token(line, column, TokenType::LeftParenthesis, "("));
			break;
		case ')':
			tokens.push_back(Token(line, column, TokenType::RightParenthesis, ")"));
			break;
		case '=':
			tokens.push_back(Token(line, column, TokenType::Assignment, "="));
			break;
		case ',':
			tokens.push_back(Token(line, column, TokenType::Comma, ","));
			break;
		case ':':
			tokens.push_back(Token(line, column, TokenType::Colon, ":"));
			break;
		case ';':
			tokens.push_back(Token(line, column, TokenType::Semicolon, ";"));
			break;
		case '{':
			tokens.push_back(Token(line, column, TokenType::LeftBrace, "{"));
			break;
		case '}':
			tokens.push_back(Token(line, column, TokenType::RightBrace, "}"));
			break;
		case '[':
			tokens.push_back(Token(line, column, TokenType::LeftBracket, "["));
			break;
		case ']':
			tokens.push_back(Token(line, column, TokenType::RightBracket, "]"));
			break;
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
			name += c;
			continue;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			number += c;
			parsingNumber = true;
			continue;
		case '.':
			if (parsingNumber)
			{
				if (number.find('.') != std::string::npos)
				{ // number contains '.'
					return {tokens, "Invalid number"};
				}

				number += c;
				continue;
			}
			else
			{
				tokens.push_back(Token(line, column, TokenType::Dot, "."));
			}
			break;
		default:
			return {tokens, "Invalid character"};
		}
	}

	if (!name.empty())
	{
		if (name == "int" || name == "float")
		{
			tokens.push_back(Token(line, column, TokenType::Keyword, name));
		}
		else
		{
			tokens.push_back(Token(line, column, TokenType::Identifier, name));
		}
	}

	if (!number.empty())
	{
		if (number.find('.') != std::string::npos)
		{ // if contains '.' then it is a float
			tokens.push_back(Token(line, column, TokenType::Float, number));
		}
		else
		{
			tokens.push_back(Token(line, column, TokenType::Integer, number));
		}
	}

	tokens.push_back(Token(line, column, TokenType::Eof, ""));

	return {tokens, error};
}
