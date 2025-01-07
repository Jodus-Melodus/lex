#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include "Token.h"
#include "Node.h"
#include "Parser.h"
#include "Lexer.h"
#include "Interpreter.h"

int main()
{
	std::string sourceCode = "5 + 3 /25 * 2.4";
	std::cout << sourceCode << std::endl;

	Lexer lexer(sourceCode);
	LexerResult result = lexer.tokenize();
	std::deque<Token> tokens = result.tokens;
	std::string error = result.error;

	if (!error.empty())
	{
		std::cout << error << std::endl;
		return 1;
	}

	for (Token token : tokens)
	{
		std::cout << token.toString() << '\n';
	}

	Parser parser(tokens);
	ParserResult parserResult = parser.parse();
	Node *ast = parserResult.node;
	std::vector<std::string> errors = parserResult.errors;

	if (!errors.empty())
	{
		for (std::string error : errors)
		{
			std::cout << error << std::endl;
		}
		return 1;
	}

	for (Node *node : static_cast<Scope *>(ast)->body)
	{
		std::cout << node->toString() << std::endl;
	}

	Interpreter interpreter(ast);
	RuntimeValue* res = interpreter.interpret();

	std::cout << res->toString() << std::endl;

	return 0;
}