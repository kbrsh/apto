#include "parser.h"

typedef Token Terminal;
typedef union {
	Terminal* terminal;
	union NonTerminal* nonterminal;
} NonTerminal;

typedef union {
	Terminal* terminal;
	NonTerminal* nonterminal;
}* Alternate;

typedef Alternate** Parser;

void parse(Tokens tokens) {

}
