#ifndef apto_scanner
#define apto_scanner

#include "../util/util.h"

typedef enum {
	TOKEN_EQUALS,
	TOKEN_COLON,
	TOKEN_LEFT_PAREN,
	TOKEN_RIGHT_PAREN,
	TOKEN_LEFT_BRACKET,
	TOKEN_RIGHT_BRACKET,
	TOKEN_VAR
} TokenType;

typedef struct {
	TokenType type;
	const char* start;
	const char* end;
} Token;

ARRAY_DECLARATION(Token, Tokens)

typedef enum {
	STATE_START,
	STATE_END,
	STATE_WHITESPACE,
	STATE_EQUALS,
	STATE_COLON,
	STATE_LEFT_PAREN,
	STATE_RIGHT_PAREN,
	STATE_LEFT_BRACKET,
	STATE_RIGHT_BRACKET,
	STATE_VAR
} StateType;

typedef struct {
	StateType type;
	const char* start;
	const char* current;
	Tokens tokens;
} State;

Tokens scan(const char* source);

#endif
