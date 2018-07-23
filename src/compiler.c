#include "compiler.h"
#include "scanner/scanner.h"

void compile(const char* source) {
	Tokens tokens = scan(source);
	destroyTokens(&tokens);
}
