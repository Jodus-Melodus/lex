#include "Interpreter.h"

RuntimeValue *Interpreter::interpretBinaryExpression(BinaryExpression *node)
{
	RuntimeValue *left = this->interpretNode(node->left);
	char operand = node->op;
	RuntimeValue *right = this->interpretNode(node->right);

	switch (operand)
	{
	case '+':
		if (auto i1 = dynamic_cast<IntegerValue *>(left))
		{
			if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return new IntegerValue(i1->value + i2->value);
			}
			else if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return new FloatValue(static_cast<float>(i1->value) + f2->value);
			}
		}
		else if (auto f1 = dynamic_cast<FloatValue *>(left))
		{
			if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return new FloatValue(f1->value + f2->value);
			}
			else if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return new FloatValue(f1->value + static_cast<float>(i2->value));
			}
		}
		break;
	case '-':
		if (auto i1 = dynamic_cast<IntegerValue *>(left))
		{
			if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return new IntegerValue(i1->value - i2->value);
			}
			else if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return new FloatValue(static_cast<float>(i1->value) - f2->value);
			}
		}
		else if (auto f1 = dynamic_cast<FloatValue *>(left))
		{
			if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return new FloatValue(f1->value - f2->value);
			}
			else if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return new FloatValue(f1->value - static_cast<float>(i2->value));
			}
		}
		break;
	case '*':
		if (auto i1 = dynamic_cast<IntegerValue *>(left))
		{
			if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return new IntegerValue(i1->value * i2->value);
			}
			else if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return new FloatValue(static_cast<float>(i1->value) * f2->value);
			}
		}
		else if (auto f1 = dynamic_cast<FloatValue *>(left))
		{
			if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return new FloatValue(f1->value * f2->value);
			}
			else if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return new FloatValue(f1->value * static_cast<float>(i2->value));
			}
		}
		break;
	case '/':
		if (auto i1 = dynamic_cast<IntegerValue *>(left))
		{
			if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return new FloatValue(static_cast<float>(i1->value) / static_cast<float>(i2->value));
			}
			else if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return new FloatValue(static_cast<float>(i1->value) / static_cast<float>(f2->value));
			}
		}
		else if (auto f1 = dynamic_cast<FloatValue *>(left))
		{
			if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return new FloatValue(f1->value / static_cast<float>(i2->value));
			}
			else if (auto f2 = dynamic_cast<FloatValue *>(right))
			{
				return new FloatValue(f1->value / f2->value);
			}
		}
		break;
	case '%':
		if (auto i1 = dynamic_cast<IntegerValue *>(left))
		{
			if (auto i2 = dynamic_cast<IntegerValue *>(right))
			{
				return new IntegerValue(i1->value % i2->value);
			}
		}
		break;
	default:
		break;
	}

	return new NullValue();
}

RuntimeValue *Interpreter::interpret()
{
	RuntimeValue *result = new NullValue();

	for (Node *node : static_cast<Scope *>(this->ast)->body)
	{
		result = this->interpretNode(node);
	}

	return result;
}

RuntimeValue *Interpreter::interpretNode(Node *node)
{
	if (auto i = dynamic_cast<IntegerLiteral *>(node))
	{
		return new IntegerValue(i->value);
	}
	else if (auto f = dynamic_cast<FloatLiteral *>(node))
	{
		return new FloatValue(f->value);
	}
	else if (auto s = dynamic_cast<StringLiteral *>(node))
	{
		return new StringValue(s->value);
	}
	else if (auto be = dynamic_cast<BinaryExpression *>(node))
	{
		return this->interpretBinaryExpression(be);
	}
	else
	{
		return new NullValue();
	}
}
