#include <iostream>

#include "input.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, const char* argv[])
{
	const char* funcText = getFuncInput(argc, argv);

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

	printTree(syntaxTree); std::cout << std::endl;
	std::cout << calcVal(syntaxTree, 0);

#ifdef _DEBUG
	std::cin.ignore();
#endif

	return 0;
}