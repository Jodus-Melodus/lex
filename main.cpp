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

void writeToFile(std::string path, std::string contents)
{
	std::ofstream file(path);

	if (file.is_open())
	{
		file << contents;
		file.close();
	}
	else
	{
		std::cerr << "Failed to open file: " << path;
	}
}

int main()
{
	std::string sourceCode = "3 + 5 / 4 * 2 % 3 - 2";

	Lexer lexer(sourceCode);
	LexerResult result = lexer.tokenize();
	std::deque<Token> tokens = result.tokens;
	std::vector<std::string> errors = result.errors;

	if (!errors.empty())
	{
		for (std::string error : errors)
		{
			std::cout << error << std::endl;
		}
		return 1;
	}

	Parser parser(tokens);
	ParserResult parserResult = parser.parse();
	Node *ast = parserResult.node;
	errors = parserResult.errors;

	if (!errors.empty())
	{
		for (std::string error : errors)
		{
			std::cout << error << std::endl;
		}
		return 1;
	}

	writeToFile("ast.json", ast->toString());

	Interpreter interpreter(ast);
	RuntimeValue *res = interpreter.interpret();

	std::cout << res->toString() << std::endl;

	return 0;
}