#include "compiler.h"
#include "scanner/scanner.h"

void compile(const char* source) {
	Tokens tokens = scan(source);
	parse(tokens);
	destroyTokens(&tokens);
}
