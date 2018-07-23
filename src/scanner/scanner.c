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

bool transition(State* state) {
	const char current = *state->current;

	switch (state->type) {
		case STATE_START:
			if (isWhitespace(current)) {
				state->type = STATE_WHITESPACE;
				state->current += 1;
			} else if (current == '\0') {
				state->type = STATE_END;
			} else if (current == '=') {
				state->type = STATE_EQUALS;
				state->start = state->current;
				state->current += 1;
			} else if (current == ':') {
				state->type = STATE_COLON;
				state->start = state->current;
				state->current += 1;
			} else if (current == '(') {
				state->type = STATE_LEFT_PAREN;
				state->start = state->current;
				state->current += 1;
			} else if (current == ')') {
				state->type = STATE_RIGHT_PAREN;
				state->start = state->current;
				state->current += 1;
			} else if (current == '{') {
				state->type = STATE_LEFT_BRACKET;
				state->start = state->current;
				state->current += 1;
			} else if (current == '}') {
				state->type = STATE_RIGHT_BRACKET;
				state->start = state->current;
				state->current += 1;
			} else if (current == '"') {
				state->type = STATE_STRING_0;
				state->start = state->current;
				state->current += 1;
			} else {
				state->type = STATE_VAR;
				state->start = state->current;
				state->current += 1;
			}
			break;

		case STATE_END:
			return false;

		case STATE_WHITESPACE:
			if (isWhitespace(current)) {
				state->current += 1;
			} else {
				state->type = STATE_START;
			}

			break;

		case STATE_EQUALS:
			appendToken(createToken(TOKEN_EQUALS, state->start, state->current), &state->tokens);
			state->type = STATE_START;
			break;

		case STATE_COLON:
			appendToken(createToken(TOKEN_COLON, state->start, state->current), &state->tokens);
			state->type = STATE_START;
			break;

		case STATE_LEFT_PAREN:
			appendToken(createToken(TOKEN_LEFT_PAREN, state->start, state->current), &state->tokens);
			state->type = STATE_START;
			break;

		case STATE_RIGHT_PAREN:
			appendToken(createToken(TOKEN_RIGHT_PAREN, state->start, state->current), &state->tokens);
			state->type = STATE_START;
			break;

		case STATE_LEFT_BRACKET:
			appendToken(createToken(TOKEN_LEFT_BRACKET, state->start, state->current), &state->tokens);
			state->type = STATE_START;
			break;

		case STATE_RIGHT_BRACKET:
			appendToken(createToken(TOKEN_RIGHT_BRACKET, state->start, state->current), &state->tokens);
			state->type = STATE_START;
			break;

		case STATE_STRING_0:
			if (current == '"') {
				state->type = STATE_STRING_1;
			}
			state->current += 1;
			break;

		case STATE_STRING_1:
			appendToken(createToken(TOKEN_STRING, state->start, state->current), &state->tokens);
			state->type = STATE_START;
			break;

		case STATE_VAR:
			if (isWhitespace(current) || current == '(' || current == ')' || current == '{' || current == '}' || current == '\0') {
				appendToken(createToken(TOKEN_VAR, state->start, state->current), &state->tokens);
				state->type = STATE_START;
			} else {
				state->current += 1;
			}

			break;
	}

	return true;
}

void token(State* state) {
	while (transition(state));
}

Tokens scan(const char* source) {
	State state;
	Tokens tokens;

	createTokens(&tokens);

	state.type = STATE_START;
	state.current = source;
	state.tokens = tokens;

	token(&state);

	for (int i = 0; i < state.tokens.length; i++) {
		Token currentToken = getToken(i, &state.tokens);
		for (const char* c = currentToken.start; c != currentToken.end; c++) {
			printf("%c", *c);
		}
		printf("\n");
	}

	return state.tokens;
}
