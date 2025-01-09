#include "Token.h"

std::string Token::toString()
{
	return "{type: " + std::to_string(this->type) +
		   ", value: " + this->value + "}";
}
