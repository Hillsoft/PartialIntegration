#ifndef __LEXER_H__
#define __LEXER_H__

#define TOKEN_NUM 1
#define TOKEN_OPERATOR_L1 2
#define TOKEN_OPERATOR_L2 3
#define TOKEN_OPERATOR_L3 4
#define TOKEN_X 5
#define TOKEN_PARENTHESES 6

struct Token
{
	Token() { contents = ""; }
	Token(const char* contents, short type)
		: contents(contents),
		type(type)
	{}

	const char* contents;
	short type;
};

const Token* lex(const char* funcText);

#endif