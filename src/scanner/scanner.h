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
	TOKEN_STRING,
	TOKEN_VAR
} TokenType;

typedef struct {
	TokenType type;
	const char* start;
	const char* end;
} Token;

ARRAY_DECLARATION(Token, Tokens)

typedef enum {
	SCANNER_START,
	SCANNER_END,
	SCANNER_WHITESPACE,
	SCANNER_EQUALS,
	SCANNER_COLON,
	SCANNER_LEFT_PAREN,
	SCANNER_RIGHT_PAREN,
	SCANNER_LEFT_BRACKET,
	SCANNER_RIGHT_BRACKET,
	SCANNER_STRING_0,
	SCANNER_STRING_1,
	SCANNER_VAR
} ScannerType;

typedef struct {
	ScannerType type;
	const char* start;
	const char* current;
	Tokens tokens;
} Scanner;

Tokens scan(const char* source);

#endif
