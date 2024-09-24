CC=gcc
CFLAGS=-Wall -Wextra -pedantic
CINCLUDES=-I./includes

SRCS=$(wildcard src/*.c)

%_test: tests/%_test.c
	@$(CC) $< $(SRCS) $(CFLAGS) $(CINCLUDES) -o tests/$@
	@./tests/$@