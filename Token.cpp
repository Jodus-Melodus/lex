#include "Token.h"

std::string Token::toString() const
{
	return "{type: " + std::to_string(this->type) +
		   ", value: " + this->value + "}";
}
