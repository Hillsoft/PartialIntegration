#ifndef __INPUT_H__

struct UInput
{
	bool setVals[4];
	const char* func = "";
	float a = 0;
	float b = 0;
	int n = 100;
};

UInput getInput(int argc, const char* argv[]);

#endif