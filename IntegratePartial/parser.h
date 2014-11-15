#ifndef __PARSER_H__
#define __PARSER_H__

#include "lexer.h"

struct TreeNode
{
	bool isLeaf;
	bool xVal;
	int val;
	char op;
	TreeNode* leftNode;
	TreeNode* rightNode;
};

void printTree(TreeNode* tree);
float calcVal(TreeNode* tree, float x);
void parse(const Token* tokenList, TreeNode*& expTree);
void parseExpression(const Token* tokenList, TreeNode*& expTree);

#endif