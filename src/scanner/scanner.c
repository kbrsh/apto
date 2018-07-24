#include "scanner.h"

ARRAY_IMPLEMENTATION(Token, Tokens)

bool isWhitespace(const char c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

Token createToken(TokenType type, const char* start, const char* end) {
	Token token;

	token.type = type;
	token.start = start;
	token.end = end;

	return token;
}

bool transition(Scanner* scanner) {
	const char current = *scanner->current;

	switch (scanner->type) {
		case SCANNER_START:
			if (isWhitespace(current)) {
				scanner->type = SCANNER_WHITESPACE;
				scanner->current += 1;
			} else if (current == '\0') {
				scanner->type = SCANNER_END;
			} else if (current == '=') {
				scanner->type = SCANNER_EQUALS;
				scanner->start = scanner->current;
				scanner->current += 1;
			} else if (current == ':') {
				scanner->type = SCANNER_COLON;
				scanner->start = scanner->current;
				scanner->current += 1;
			} else if (current == '(') {
				scanner->type = SCANNER_LEFT_PAREN;
				scanner->start = scanner->current;
				scanner->current += 1;
			} else if (current == ')') {
				scanner->type = SCANNER_RIGHT_PAREN;
				scanner->start = scanner->current;
				scanner->current += 1;
			} else if (current == '{') {
				scanner->type = SCANNER_LEFT_BRACKET;
				scanner->start = scanner->current;
				scanner->current += 1;
			} else if (current == '}') {
				scanner->type = SCANNER_RIGHT_BRACKET;
				scanner->start = scanner->current;
				scanner->current += 1;
			} else if (current == '"') {
				scanner->type = SCANNER_STRING_0;
				scanner->start = scanner->current;
				scanner->current += 1;
			} else {
				scanner->type = SCANNER_VAR;
				scanner->start = scanner->current;
				scanner->current += 1;
			}
			break;

		case SCANNER_END:
			return false;

		case SCANNER_WHITESPACE:
			if (isWhitespace(current)) {
				scanner->current += 1;
			} else {
				scanner->type = SCANNER_START;
			}

			break;

		case SCANNER_EQUALS:
			appendToken(createToken(TOKEN_EQUALS, scanner->start, scanner->current), &scanner->tokens);
			scanner->type = SCANNER_START;
			break;

		case SCANNER_COLON:
			appendToken(createToken(TOKEN_COLON, scanner->start, scanner->current), &scanner->tokens);
			scanner->type = SCANNER_START;
			break;

		case SCANNER_LEFT_PAREN:
			appendToken(createToken(TOKEN_LEFT_PAREN, scanner->start, scanner->current), &scanner->tokens);
			scanner->type = SCANNER_START;
			break;

		case SCANNER_RIGHT_PAREN:
			appendToken(createToken(TOKEN_RIGHT_PAREN, scanner->start, scanner->current), &scanner->tokens);
			scanner->type = SCANNER_START;
			break;

		case SCANNER_LEFT_BRACKET:
			appendToken(createToken(TOKEN_LEFT_BRACKET, scanner->start, scanner->current), &scanner->tokens);
			scanner->type = SCANNER_START;
			break;

		case SCANNER_RIGHT_BRACKET:
			appendToken(createToken(TOKEN_RIGHT_BRACKET, scanner->start, scanner->current), &scanner->tokens);
			scanner->type = SCANNER_START;
			break;

		case SCANNER_STRING_0:
			if (current == '"') {
				scanner->type = SCANNER_STRING_1;
			}
			scanner->current += 1;
			break;

		case SCANNER_STRING_1:
			appendToken(createToken(TOKEN_STRING, scanner->start, scanner->current), &scanner->tokens);
			scanner->type = SCANNER_START;
			break;

		case SCANNER_VAR:
			if (isWhitespace(current) || current == '(' || current == ')' || current == '{' || current == '}' || current == '\0') {
				appendToken(createToken(TOKEN_VAR, scanner->start, scanner->current), &scanner->tokens);
				scanner->type = SCANNER_START;
			} else {
				scanner->current += 1;
			}

			break;
	}

	return true;
}

void token(Scanner* scanner) {
	while (transition(scanner));
}

Tokens scan(const char* source) {
	Scanner scanner;
	Tokens tokens;

	createTokens(&tokens);

	scanner.type = SCANNER_START;
	scanner.current = source;
	scanner.tokens = tokens;

	token(&scanner);

	return scanner.tokens;
}
