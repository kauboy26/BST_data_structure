#define INIT_CAPACITY 15

typedef struct _stack {
	int size;
	int capacity;
	int *arr;
} Stack;

/**
 * Creates a stack, of capacity INIT_CAPACITY.
 */
Stack *create_stack();

/**
 * Push an item on to the stack. In case the stack overflows, it will regrow
 * accordingly.
 *
 * @param item an int to push on to the stack.
 * @return the new size of the stack.
 */
int push_stack(Stack *stack, int item);

/**
 * Pops an item off the stack, stores the item in dataOut.
 *
 * @return the size of the stack.
 */
int pop_stack(Stack *stack, int *dataOut);

/**
 * Stores the peaked value in dataOut.
 * @return 0 if successful, -1 if an error occurred.
 */
int peak_stack(Stack *stack, int *dataOut);

/**
 * Checks whether the stack is empty.
 */
int is_stack_empty(Stack *stack);

/**
 * Clears the stack of all its items, but doesn't free the stack itself.
 * @param stack pointer to the stack.
 * @return -1 if there was an error, 0 if it was a success.
 */
int clear_stack(Stack *stack);

/**
 * Destroy the stack and all its contents (from memory).
 * @param stack pointer to the stack
 * @return -1 if there was an error, 0 if it was a success.
 */
int destroy_stack(Stack *stack);

/**
 * @return the size, -1 if an error occurred.
 */
int stack_size(Stack *stack);

/**
 * @return the capacity, -1 if an error occurred.
 */
int stack_capacity(Stack *stack);
