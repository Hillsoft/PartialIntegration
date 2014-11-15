#include "trapezium.h"

float trapeziumIntegrate(TreeNode* tree, float a, float b, int n)
{
	if (a > b)
		throw "a must be less than b";

	float h = (b - a) / n;

	float result = 0;
	float prevX = calcVal(tree, a);
	for (int i = 1; i <= n; i++)
	{
		float curX = calcVal(tree, a + h * i);
		result += prevX + curX;
		prevX = curX;
	}

	return result * h / 2;
}