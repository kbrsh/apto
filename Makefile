CC = gcc-7
CFLAGS = -Wall -g -march=native
src = $(shell find . -name "*.c")
obj = $(src:.c=.o)

apto: $(obj)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(obj) apto
