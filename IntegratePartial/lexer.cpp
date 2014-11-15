#include <iostream>
#include <vector>

#include "lexer.h"

const Token* lex(const char* funcText)
{
	int strLen = strlen(funcText);

	char* curNum = new char[10];
	int curNumLength = 0;
	std::vector<Token> tokenList = std::vector<Token>();
	char* curCont;

	for (int i = 0; i < strLen; i++)
	{
		switch (funcText[i])
		{
		case '+':
		case '-':
			curCont = new char[2];
			curCont[0] = funcText[i];
			curCont[1] = 0;
			tokenList.push_back(Token(curCont, TOKEN_OPERATOR_L1));
			break;

		case '*':
		case '/':
			curCont = new char[2];
			curCont[0] = funcText[i];
			curCont[1] = 0;
			tokenList.push_back(Token(curCont, TOKEN_OPERATOR_L2));
			break;

		case '^':
			curCont = new char[2];
			curCont[0] = funcText[i];
			curCont[1] = 0;
			tokenList.push_back(Token(curCont, TOKEN_OPERATOR_L3));
			break;

		case 'x':
		case 'X':
			curCont = new char[2];
			curCont[0] = funcText[i];
			curCont[1] = 0;
			tokenList.push_back(Token(curCont, TOKEN_X));
			break;

		case '(':
			curCont = new char[2];
			curCont[0] = funcText[i];
			curCont[1] = 0;
			tokenList.push_back(Token(curCont, TOKEN_OPEN_PARENTHESES));
			break;

		case ')':
			curCont = new char[2];
			curCont[0] = funcText[i];
			curCont[1] = 0;
			tokenList.push_back(Token(curCont, TOKEN_CLOSE_PARENTHESES));
			break;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (curNumLength < 10)
			{
				curNum[curNumLength] = funcText[i];
				curNumLength++;

				if (!(funcText[i+1] >= '0' && funcText[i+1] <= '9'))
				{
					curNum[curNumLength] = 0;
					curCont = new char[curNumLength];
					memcpy(curCont, curNum, sizeof(char) * (curNumLength + 1));
					tokenList.push_back(Token(curCont, TOKEN_NUM));
					curNumLength = 0;
				}
			}
			break;

		case ' ':
		case '\t':
			break;
		default:
			throw "Invalid character";
		}
	}
	delete[] curNum;

	Token* outList = new Token[tokenList.size() + 1];
	for (int i = 0; i < tokenList.size(); i++)
	{
		outList[i] = tokenList.at(i);
	}

	return outList;
}