CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra
DEBUG_FLAGS = -g -DDEBUG

run-stack-test : stack.o test_stack.o stack.h
	$(CC) $(CFLAGS) stack.o test_stack.o -o test
	./test

stack.o : stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

test_stack.o : test_stack.c stack.h
	$(CC) $(CFLAGS) -c test_stack.c

clean :
	rm -f *.o test