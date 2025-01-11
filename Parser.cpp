#include "Parser.h"

Token *Parser::peek()
{
	if (this->tokens.empty())
	{
		return nullptr;
	}
	Token *x = &this->tokens.front();
	return x;
}

Token *Parser::eat()
{
	if (this->tokens.empty())
	{
		return nullptr;
	}
	Token *token = new Token(this->tokens.front());
	this->tokens.pop_front();
	return token;
}

ParserResult Parser::parse()
{
	while (this->peek()->type != TokenType::Eof)
	{
		ParserResult result = this->parseStatement();
		this->nodes.push_back(result.node);
		this->errors.insert(this->errors.end(), result.errors.begin(), result.errors.end());
	}

	this->eat();
	return {new Scope(this->nodes), this->errors};
}

ParserResult Parser::parseStatement()
{
	return this->parseExpression();
}

ParserResult Parser::parseExpression()
{
	return this->parseAdditiveExpression();
}

ParserResult Parser::parseAdditiveExpression()
{
	ParserResult result = this->parseMultiplicativeExpression();
	if (!result.errors.empty())
	{
		return result;
	}

	Node *left = result.node;
	char operators[] = {'+', '-'};

	while (this->peek()->type == TokenType::BinaryOperator)
	{
		if (std::find(std::begin(operators), std::end(operators), this->peek()->value[0]) != std::end(operators))
		{
			char operand = this->eat()->value[0];
			result = this->parseMultiplicativeExpression();
			if (!result.errors.empty())
			{
				return result;
			}

			left = new BinaryExpression(left, result.node, operand);
		}
		else
		{
			break;
		}
	}

	return {left, {}};
}

ParserResult Parser::parseMultiplicativeExpression()
{
	ParserResult result = this->parsePrimaryExpression();
	if (!result.errors.empty())
	{
		return result;
	}

	Node *left = result.node;
	char operators[] = {'*', '%', '/'};

	while (this->peek()->type == TokenType::BinaryOperator)
	{
		if (std::find(std::begin(operators), std::end(operators), this->peek()->value[0]) != std::end(operators))
		{
			char operand = this->eat()->value[0];
			result = this->parsePrimaryExpression();
			if (!result.errors.empty())
			{
				return result;
			}

			left = new BinaryExpression(left, result.node, operand);
		}
		else
		{
			break;
		}
	}

	return {left, {}};
}

ParserResult Parser::parsePrimaryExpression()
{
	Token *token = this->eat();

	switch (token->type)
	{
	case TokenType::Integer:
		return {new IntegerLiteral(std::stoi(token->value)), {}};
	case TokenType::Float:
		return {new FloatLiteral(std::stof(token->value)), {}};
	case TokenType::Identifier:
		return {new IdentifierLiteral(token->value), {}};
	case TokenType::String:
		return {new StringLiteral(token->value), {}};
	default:
		return {new NullLiteral(), {Error(std::string("Unknown token: ") + token->toString(), token->line, token->column)}};
	}
}
