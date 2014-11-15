#include <iostream>
#include <string>

#include "parser.h"

inline bool isLeafNode(TreeNode* tree)
{
	return tree->isLeaf;
}

inline bool isXVal(TreeNode* tree)
{
	return tree->xVal;
}

inline int leafValue(TreeNode* tree)
{
	return tree->val;
}

inline char nodeOperator(TreeNode* tree)
{
	return tree->op;
}

inline TreeNode* leftOf(TreeNode* tree)
{
	return tree->leftNode;
}

inline TreeNode* rightOf(TreeNode* tree)
{
	return tree->rightNode;
}

TreeNode* buildLeaf(int number)
{
	TreeNode* newNode = new TreeNode();

	newNode->isLeaf = true;
	newNode->val = number;
	newNode->leftNode = NULL;
	newNode->rightNode = NULL;
	newNode->op = '\0';
	newNode->xVal = false;

	return newNode;
}

TreeNode* buildLeafX()
{
	TreeNode* newNode = new TreeNode();

	newNode->xVal = true;
	newNode->isLeaf = true;
	newNode->val = 0;
	newNode->leftNode = NULL;
	newNode->rightNode = NULL;
	newNode->op = '\0';

	return newNode;
}

TreeNode* buildNode(TreeNode* op1, TreeNode* op2, char op)
{
	TreeNode* newNode = new TreeNode();

	newNode->isLeaf = false;
	newNode->leftNode = op1;
	newNode->rightNode = op2;
	newNode->op = op;
	newNode->val = 0;
	newNode->xVal = false;

	return newNode;
}

float calcVal(TreeNode* tree, float x)
{
	float result = 0;

	if (isLeafNode(tree))
	{
		if (isXVal(tree))
			return x;
		else
			return leafValue(tree);
	}
	else
	{
		switch (nodeOperator(tree))
		{
		case '+':
			result = calcVal(leftOf(tree), x) + calcVal(rightOf(tree), x);
			break;
		case '-':
			result = calcVal(leftOf(tree), x) - calcVal(rightOf(tree), x);
			break;
		case '*':
			result = calcVal(leftOf(tree), x) * calcVal(rightOf(tree), x);
			break;
		case '/':
			result = calcVal(leftOf(tree), x) / calcVal(rightOf(tree), x);
			break;
		default:
			throw "Error evaluating syntax tree";
		}
	}

	return result;
}

void printTree(TreeNode* tree)
{
	if (isLeafNode(tree))
	{
		if (isXVal(tree))
		{
			std::cout << "x";
		}
		else
		{
			std::cout << leafValue(tree);
		}
	}
	else
	{
		std::cout << "(";
		printTree(leftOf(tree));
		std::cout << nodeOperator(tree);
		printTree(rightOf(tree));
		std::cout << ")";
	}
}

int curPos;

void parseExponent(const Token* tokenList, TreeNode*& expTree)
{
	if (tokenList[curPos].contents[0] != '\0' &&
		tokenList[curPos].type == TOKEN_OPEN_PARENTHESES)
	{
		curPos++;
		parseExpression(tokenList, expTree);

		if (tokenList[curPos].type != TOKEN_CLOSE_PARENTHESES)
			throw "Expected token ')'";

		curPos++;
	}
	else if (tokenList[curPos].contents[0] != '\0' &&
		tokenList[curPos].type == TOKEN_X)
	{
		expTree = buildLeafX();
		curPos++;
	}
	else if (tokenList[curPos].contents[0] != '\0' &&
		tokenList[curPos].type == TOKEN_NUM)
	{
		expTree = buildLeaf(std::stoi(tokenList[curPos].contents));
		curPos++;
	}
	else
	{
		throw "Cannot have two consecutive operators";
	}
}

void parseFactor(const Token* tokenList, TreeNode*& expTree)
{
	TreeNode* tempTree = NULL;
	char op;

	parseExponent(tokenList, expTree);
	while (tokenList[curPos].contents[0] != '\0' &&
		tokenList[curPos].type == TOKEN_OPERATOR_L3)
	{
		op = tokenList[curPos].contents[0];
		curPos++;

		parseExponent(tokenList, tempTree);
		expTree = buildNode(expTree, tempTree, op);
	}
}

void parseTerm(const Token* tokenList, TreeNode*& expTree)
{
	TreeNode* tempTree = NULL;
	char op;

	parseFactor(tokenList, expTree);
	while (tokenList[curPos].contents[0] != '\0' &&
		tokenList[curPos].type == TOKEN_OPERATOR_L2)
	{
		op = tokenList[curPos].contents[0];
		curPos++;

		parseFactor(tokenList, tempTree);
		expTree = buildNode(expTree, tempTree, op);
	}
}

void parseExpression(const Token* tokenList, TreeNode*& expTree)
{
	curPos = 0;
	TreeNode* tempTree = NULL;
	char op;

	parseTerm(tokenList, expTree);
	while (tokenList[curPos].contents[0] != '\0' &&
		tokenList[curPos].type == TOKEN_OPERATOR_L1)
	{
		op = tokenList[curPos].contents[0];
		curPos++;

		parseTerm(tokenList, tempTree);
		expTree = buildNode(expTree, tempTree, op);
	}

	if (tokenList[curPos].contents[0] != '\0')
		throw "Did not reach end";
}