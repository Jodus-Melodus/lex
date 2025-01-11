#include "Interpreter.h"

InterpreterResult Interpreter::interpretBinaryExpression(BinaryExpression *node)
{
	InterpreterResult leftResult = this->interpretNode(node->left);
	if (!leftResult.error.isEmpty())
	{
		return leftResult;
	}
	RuntimeValue *left = leftResult.value;

	InterpreterResult rightResult = this->interpretNode(node->right);
	if (!rightResult.error.isEmpty())
	{
		return rightResult;
	}
	RuntimeValue *right = rightResult.value;

	char operand = node->op;

	switch (operand)
	{
	case '+':
		if (auto i1 = dynamic_cast<IntegerValue *>(left))
		{
			if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return {new IntegerValue(i1->value + i2->value), Error()};
			}
			else if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return {new FloatValue(static_cast<float>(i1->value) + f2->value), Error()};
			}
			else
			{
				return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
			}
		}
		else if (auto f1 = dynamic_cast<FloatValue *>(left))
		{
			if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return {new FloatValue(f1->value + f2->value), Error()};
			}
			else if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return {new FloatValue(f1->value + static_cast<float>(i2->value)), Error()};
			}
			else
			{
				return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
			}
		}
		else if (auto s1 = dynamic_cast<StringValue *>(left))
		{
			if (auto s2 = dynamic_cast<StringValue *>(right))
			{
				return {new StringValue(s1->value + s2->value), Error()};
			}
			else
			{
				return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
			}
		}
		else
		{
			return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
		}
		break;
	case '-':
		if (auto i1 = dynamic_cast<IntegerValue *>(left))
		{
			if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return {new IntegerValue(i1->value - i2->value), Error()};
			}
			else if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return {new FloatValue(static_cast<float>(i1->value) - f2->value), Error()};
			}
			else
			{
				return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
			}
		}
		else if (auto f1 = dynamic_cast<FloatValue *>(left))
		{
			if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return {new FloatValue(f1->value - f2->value), Error()};
			}
			else if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return {new FloatValue(f1->value - static_cast<float>(i2->value)), Error()};
			}
			else
			{
				return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
			}
		}
		else
		{
			return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
		}
		break;
	case '*':
		if (auto i1 = dynamic_cast<IntegerValue *>(left))
		{
			if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return {new IntegerValue(i1->value * i2->value), Error()};
			}
			else if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return {new FloatValue(static_cast<float>(i1->value) * f2->value), Error()};
			}
			else
			{
				return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
			}
		}
		else if (auto f1 = dynamic_cast<FloatValue *>(left))
		{
			if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return {new FloatValue(f1->value * f2->value), Error()};
			}
			else if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return {new FloatValue(f1->value * static_cast<float>(i2->value)), Error()};
			}
			else
			{
				return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
			}
		}
		else
		{
			return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
		}
		break;
	case '/':
		if (auto i1 = dynamic_cast<IntegerValue *>(left))
		{
			if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return {new FloatValue(static_cast<float>(i1->value) / static_cast<float>(i2->value)), Error()};
			}
			else if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return {new FloatValue(static_cast<float>(i1->value) / static_cast<float>(f2->value)), Error()};
			}
			else
			{
				return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
			}
		}
		else if (auto f1 = dynamic_cast<FloatValue *>(left))
		{
			if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return {new FloatValue(f1->value / static_cast<float>(i2->value)), Error()};
			}
			else if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return {new FloatValue(f1->value / f2->value), Error()};
			}
			else
			{
				return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
			}
		}
		else
		{
			return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
		}
		break;
	case '%':
		if (auto i1 = dynamic_cast<IntegerValue *>(left))
		{
			if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return {new IntegerValue(i1->value % i2->value), Error()};
			}
			else
			{
				return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
			}
		}
		else
		{
			return {new NullValue(), Error(std::string("Unsupported operand for types"), 0, 0)};
		}
		break;
	default:
		return {new NullValue(), Error(std::string("Unknown operand: '") + operand + '\"', 0, 0)};
	}
}

InterpreterResult Interpreter::interpret()
{
	InterpreterResult result = {new NullValue(), Error()};

	for (Node *node : static_cast<Scope *>(this->ast)->body)
	{
		result = this->interpretNode(node);

		if (!result.error.isEmpty())
		{
			return result;
		}
	}

	return result;
}

InterpreterResult Interpreter::interpretNode(Node *node)
{
	if (auto i = dynamic_cast<IntegerLiteral *>(node))
	{
		return {new IntegerValue(i->value), Error()};
	}
	else if (auto f = dynamic_cast<FloatLiteral *>(node))
	{
		return {new FloatValue(f->value), Error()};
	}
	else if (auto s = dynamic_cast<StringLiteral *>(node))
	{
		return {new StringValue(s->value), Error()};
	}
	else if (auto be = dynamic_cast<BinaryExpression *>(node))
	{
		return this->interpretBinaryExpression(be);
	}
	else
	{
		return {new NullValue(), Error(std::string("Invalid node \"") + node->toString() + std::string("\" found"), 0, 0)};
	}
}
