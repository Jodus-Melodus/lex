#pragma once
#include <string>

class RuntimeValue
{
public:
	RuntimeValue() {};
	virtual std::string toString() = 0;
	virtual ~RuntimeValue() {};
};

class IntegerValue : public RuntimeValue
{
public:
	int value;
	IntegerValue(int value) : value(value) {};
	std::string toString() override { return std::to_string(this->value); }
	~IntegerValue() {};
};

class FloatValue : public RuntimeValue
{
public:
	float value;
	FloatValue(float value) : value(value) {};
	std::string toString() override { return std::to_string(this->value); }
	~FloatValue() {};
};

class StringValue : public RuntimeValue
{
public:
	std::string value;
	StringValue(std::string value) : value(value) {};
	std::string toString() override { return this->value; }
	~StringValue() {};
};

class NullValue : public RuntimeValue
{
public:
	NullValue() {};
	std::string toString() override { return ""; }
	~NullValue() {};
};