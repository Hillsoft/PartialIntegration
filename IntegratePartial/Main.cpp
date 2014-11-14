#include <iostream>

#include "input.h"
#include "lexer.h"

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

	for (int i = 0; tokenList[i].contents[0] != 0; i++)
	{
		std::cout << "Type: " << tokenList[i].type << "; Val: " << tokenList[i].contents << "\n";
	}

#ifdef _DEBUG
	std::cin.ignore();
#endif

	return 0;
}