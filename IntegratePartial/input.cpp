#include <iostream>
#include <string>

#include "input.h"

const char* getFuncInput(int argc, const char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-y") && i < argc - 1)
		{
			i++;
			return argv[i];
		}
	}

	std::string func;
	std::cout << "y = ";
	std::getline(std::cin, func);

	char* str = new char[func.length() + 1];
	std::strcpy(str, func.c_str());
	return str;
}