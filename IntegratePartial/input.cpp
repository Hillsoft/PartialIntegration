#include <iostream>
#include <string>

#include "input.h"

UInput getInput(int argc, const char* argv[])
{
	UInput input;
	input.setVals[0] = false;
	input.setVals[1] = false;
	input.setVals[2] = false;
	input.setVals[3] = false;

	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-y") && i < argc - 1)
		{
			input.setVals[0] = true;
			i++;
			input.func = argv[i];
		}
		if (!strcmp(argv[i], "-a") && i < argc - 1)
		{
			input.setVals[1] = true;
			i++;
			input.a = std::stof(argv[i]);
		}
		if (!strcmp(argv[i], "-b") && i < argc - 1)
		{
			input.setVals[2] = true;
			i++;
			input.b = std::stof(argv[i]);
		}
		if (!strcmp(argv[i], "-n") && i < argc - 1)
		{
			input.setVals[3] = true;
			i++;
			input.n = std::stoi(argv[i]);
		}
	}

	if (!input.setVals[0])
	{
		std::string func;
		std::cout << "y = ";
		std::getline(std::cin, func);

		char* str = new char[func.length() + 1];
		std::strcpy(str, func.c_str());
		input.func = str;
	}
	if (!input.setVals[1])
	{
		std::cout << "a = ";
		std::cin >> input.a;
	}
	if (!input.setVals[2])
	{
		std::cout << "b = ";
		std::cin >> input.b;
	}
	if (!input.setVals[3])
	{
		input.n = 10;
	}

	return input;
}