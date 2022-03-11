CFLAGS = -Wall -Wextra -g -std=c99
CFILES = main.c trie.c book.c
INPUT = input
OUTPUT = output

build: *.c
	gcc $(CFLAGS) $(CFILES) -o tema3

run: build
	./tema3 $(INPUT) $(OUTPUT)

clean: tema3
	rm -f tema3
