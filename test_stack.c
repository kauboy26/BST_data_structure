#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(void) {

	Stack *stack;
	int data;

	printf("Create new stack.\n");
	stack = create_stack();
	assert(stack_size(stack) == 0);
	assert(stack_capacity(stack) == INIT_CAPACITY);
	printf("passes\n\n");

	printf("Push test. \n");
	for (int i = 0; i < INIT_CAPACITY; i++) {
		printf("pushing %d\n", i);
		assert(push_stack(stack, i));
	}

	// Causing overflow.
	printf("pushing %d\n", 15);
	assert(push_stack(stack, 15) == INIT_CAPACITY + 1);
	assert(stack_capacity(stack) == INIT_CAPACITY * 2);
	// should have INIT_CAPACITY + 1 elements as of now.

	for (int i = 0; i < INIT_CAPACITY; i++) {
		printf("pushing %d\n", i + INIT_CAPACITY + 1);
		assert(push_stack(stack, i + INIT_CAPACITY + 1) == i + INIT_CAPACITY + 2);
	}

	printf("Size should be %d, is %d\n", INIT_CAPACITY * 2 + 1, stack_size(stack));
	assert(stack_size(stack) == INIT_CAPACITY + INIT_CAPACITY + 1);
	// should have INIT_CAP * 2 + 1 elems.
	printf("Capacity should be %d, is %d\n", INIT_CAPACITY * 4, stack_capacity(stack));
	assert(stack_capacity(stack) == INIT_CAPACITY * 4);
	// would have regrown twice, so should have CAP * 4 space.
	printf("passes\n\n");


	printf("Pop test\n");
	printf("size is %d\n", stack_size(stack));
	int size_r = stack_size(stack);
	for (int i = 0; i < size_r; i++) {
		assert(pop_stack(stack, &data) == INIT_CAPACITY * 2 - i);
		printf("Size should be %d, is %d\n", INIT_CAPACITY * 2 - i, stack_size(stack));
		assert(data == INIT_CAPACITY * 2 - i);
	}

	printf("Size should be 0, is: %d\n", stack_size(stack));
	assert(stack_size(stack) == 0);
	printf("popping empty stack, expecting -1\n");
	assert(pop_stack(stack, &data) == -1);
	printf("passes\n\n");

	printf("clear test\n");
	for (int i = 0; i < 10; i++) {
		assert(push_stack(stack, i) == i + 1);
	}
	assert(pop_stack(stack, &data) == 9);
	assert(data == 9);
	assert(peak_stack(stack, &data) == 9);
	assert(data == 8);

	assert(clear_stack(stack) == 0);
	assert(stack_size(stack) == 0);
	assert(pop_stack(stack, &data) == -1);
	assert(clear_stack(NULL) == -1);
	printf("passes\n\n");

	printf("destroy test\n");
	size_r = stack_capacity(stack);
	for (int i = 0; i < INIT_CAPACITY * 3; i++) {
		assert(push_stack(stack, i) == i + 1);
	}
	// the capacity should have stayed the same.
	assert(stack_capacity(stack) == size_r);
	printf("the size should be %d, is %d\n", INIT_CAPACITY * 3, stack_size(stack));
	assert(peak_stack(stack, &data) == INIT_CAPACITY * 3);
	assert(data == INIT_CAPACITY * 3 - 1);
	assert(destroy_stack(stack) == 0);
	assert(destroy_stack(NULL) == -1);
	printf("passes\n\n");

	printf("All cases passed.\n");
}