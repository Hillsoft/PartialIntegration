#include <iostream>

#include "input.h"
#include "lexer.h"
#include "parser.h"
#include "trapezium.h"

int main(int argc, const char* argv[])
{
	UInput input = getInput(argc, argv);
	const char* funcText = input.func;

	const Token* tokenList;
	try
	{
		tokenList = lex(funcText);
	}
	catch (const char* ex)
	{
		std::cout << ex;

#ifdef _DEBUG
		std::cin.ignore();
#endif

		return 1;
	}

	TreeNode* syntaxTree;
	try
	{
		parseExpression(tokenList, syntaxTree);
	}
	catch (const char* ex)
	{
		std::cout << ex;

#ifdef _DEBUG
		std::cin.ignore();
#endif

		return 1;
	}

	std::cout << trapeziumIntegrate(syntaxTree, input.a, input.b, input.n) << std::endl;

#ifdef _DEBUG
	std::cin.ignore(); std::cin.ignore();
#endif

	return 0;
}