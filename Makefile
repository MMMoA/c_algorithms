.PHONY: all clean

CC=gcc
DEBUG=-O0 -g
LDFLAGS=-fsanitize=address#-lasan
CFLAGS=-Werror -Wall -pedantic -fsanitize=address -std=c11 $(DEBUG) $(OPTIONAL_CFLAGS)

OPTIONAL_CFLAGS= -Wcomment -Wformat -Wimplicit -Wparentheses -Wreturn-type -Wunused -Wstrict-prototypes -Wmissing-prototypes

all: string_operations

string_operations: levenshtein strings

strings: libstring strings_test

strings_test: string_operations/stringlib_test.o
	$(CC) $(LDFLAGS) -o $@ $^

libstring: string_operations/string_operations.o
	ar rcs $@.a $^

levenshtein: string_operations/levenshtein_DPtable.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

dist-clean:
	rm -f $(shell find . -not -name "." -not -name "*.[ch]" -not -name "*.py" -not -name "Makefile")

clean:
	rm -f ./*.o
