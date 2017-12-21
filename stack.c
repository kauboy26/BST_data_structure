#include <stdlib.h>
#include "stack.h"

static int _regrow(Stack *stack);

/**
 * Creates a stack, of capacity INIT_CAPACITY.
 * @return pointer to the new stack, or NULL if there was an error.
 */
Stack *create_stack() {
	Stack *stack = malloc(sizeof(Stack));
	if (stack == NULL) {
		return NULL;
	}

	// set size, capacity, create the backing array.
	stack->size = 0;
	stack->capacity = INIT_CAPACITY;
	stack->arr = malloc(sizeof(int) * stack->capacity);
	if (stack->arr == NULL) {
		free(stack);
		return NULL;
	}

	return stack;
}

/**
 * Push an item on to the stack. In case the stack overflows, it will regrow
 * accordingly.
 *
 * @param item an int to push on to the stack.
 * @return the new size of the stack. (-1 if there was an error)
 */
int push_stack(Stack *stack, int item) {
	if (stack == NULL) {
		return -1;
	}

	// is it already full?
	if (stack->size == stack->capacity) {
		if(_regrow(stack) == -1) {
			return -1;
		}
	}

	stack->arr[stack->size] = item;
	stack->size++;

	return stack->size;
}

/**
 * Pops an item off the stack.
 *
 * @param stack The stack
 * @param dataOut where the popped item should be stored.
 * @return the size of the stack (-1 if there was an error)
 */
int pop_stack(Stack *stack, int *dataOut) {
	if (stack == NULL || dataOut == NULL || stack->size == 0) {
		return -1;
	}

	stack->size--;
	*dataOut = stack->arr[stack->size];
	return stack->size;
}

/**
 * Stores the peaked value in dataOut.
 * @return the size of the stack if successful, -1 if an error occurred.
 */
int peak_stack(Stack *stack, int *dataOut) {
	if (stack == NULL || dataOut == NULL || stack->size == 0) {
		return -1;
	}

	*dataOut = stack->arr[stack->size - 1];
	return stack->size;
}

/**
 * Checks whether the stack is empty.
 * @param stack pointer to the stack.
 * @return -1 if there was an error, 0 if it was a success.
 */
int is_stack_empty(Stack *stack) {
	if (stack == NULL) {
		return -1;
	}
	return stack->size == 0;
}

/**
 * Clears the stack of all its items, but doesn't free the stack itself.
 * @param stack pointer to the stack.
 * @return -1 if there was an error, 0 if it was a success.
 */
int clear_stack(Stack *stack) {
	if (stack == NULL) {
		return -1;
	}
	stack->size = 0;
	return 0;
}

/**
 * Destroy the stack and all its contents (from memory).
 * @param stack pointer to the stack
 * @return -1 if there was an error, 0 if it was a success.
 */
int destroy_stack(Stack *stack) {
	if (stack == NULL) {
		return -1;
	}

	// free the array.
	free(stack->arr);
	free(stack);
	return 0;
}

/**
 * @return the size, -1 if an error occurred.
 */
int stack_size(Stack *stack) {
	if (stack == NULL) {
		return -1;
	}

	return stack->size;
}

/**
 * @return the capacity, -1 if an error occurred.
 */
int stack_capacity(Stack *stack) {
	if (stack == NULL) {
		return -1;
	}

	return stack->capacity;
}

/**
 * Regrows the backing array to length * 2, and copies over the elements.
 * @param stack The stack to regrow
 * @return the new capacity of the stack if it was a success, -1 if it was a failure.
 */
static int _regrow(Stack *stack) {
	if (stack == NULL) {
		return -1;
	}

	int new_capacity = stack->capacity * 2;
	int *temp = realloc(stack->arr, sizeof(int) * new_capacity);
	if (temp == NULL) {
		return -1;
	}
	stack->arr = temp;
	stack->capacity = new_capacity;

	return new_capacity;
}