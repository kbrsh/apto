#include "src/compiler.h"
#include "src/util/util.h"

int main(int argc, const char* argv[]) {
	FILE* file = fopen(argv[1], "r");

	fseek(file, 0L, SEEK_END);
	size_t size = ftell(file);
	rewind(file);

	char* buffer = (char*)malloc(size + 1);
	fread(buffer, 1, size, file);
	buffer[size] = '\0';

	compile(buffer);

	fclose(file);
	free(buffer);
	return 0;
}
