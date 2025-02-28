#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <vector>
#include "Token.h"
#include "Node.h"
#include "Parser.h"
#include "Lexer.h"
#include "Interpreter.h"

static std::string readFromFile(std::string path)
{
	std::ifstream file(path);

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << path << std::endl;
		return "";
	}

	std::string contents = "";
	std::string line = "";

	while (std::getline(file, line))
	{
		contents += line + '\n';
	}

	file.close();
	return contents;
}

static void writeToFile(std::string path, std::string contents)
{
	std::ofstream file(path);

	if (file.is_open())
	{
		file << contents;
		file.close();
	}
	else
	{
		std::cerr << "Failed to open file: " << path << std::endl;
	}
}

static int run(std::string path)
{
	std::string sourceCode = readFromFile(path);

	if (sourceCode.empty())
	{
		std::cerr << "Source code is empty" << std::endl;
		return 1;
	}

	Lexer lexer(sourceCode);
	LexerResult lexerResult = lexer.tokenize();
	std::deque<Token> tokens = lexerResult.tokens;
	std::vector<Error> errors = lexerResult.errors;

	if (!errors.empty())
	{
		for (Error error : errors)
		{
			std::cerr << error.toString() << std::endl;
		}
		return 1;
	}

	Parser parser(tokens);
	ParserResult parserResult = parser.parse();
	Node *ast = parserResult.node;
	errors = parserResult.errors;

	if (!errors.empty())
	{
		for (Error error : errors)
		{
			std::cerr << error.toString() << std::endl;
		}
		return 1;
	}

	writeToFile("ast.json", ast->toString());

	Interpreter interpreter(ast);
	InterpreterResult interpreterResult = interpreter.interpret();
	RuntimeValue *res = interpreterResult.value;
	Error err = interpreterResult.error;

	if (!err.isEmpty())
	{
		std::cerr << err.toString() << std::endl;
		return 1;
	}

	std::cout << res->toString() << std::endl;

	return 0;
}

int main(int argc, char *argv[])
{
	switch (argc)
	{
	case 1:
		return run(std::string("test.txt"));
	case 2:
		return run(argv[1]);
	default:
		std::cerr << "invalid arguments" << std::endl;
		return 1;
	}
}