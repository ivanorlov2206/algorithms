#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define DEFAULT_CAPACITY 1

struct stack {
	int *data;
	int capacity;
	int ptr;
};

struct stack *create_stack(void)
{
	struct stack *res = malloc(sizeof(*res));
	if (!res)
		return NULL;
	res->capacity = DEFAULT_CAPACITY;
	res->data = malloc(sizeof(int) * res->capacity);
	if (!res->data) {
		free(res);
		return NULL;
	}
	res->ptr = 0;

	return res;
}

int resize(struct stack *stack, int new_size)
{
	int *new_arr;
	size_t i, limit;

	new_arr = malloc(sizeof(int) * new_size);
	if (!new_arr)
		return -1;
	limit = stack->capacity;
	if (new_size < limit)
		limit = new_size;
	for (i = 0; i < limit; i++) {
		new_arr[i] = stack->data[i];
	}
	free(stack->data);
	stack->data = new_arr;
	stack->capacity = new_size;

	return 0;
}

int push(struct stack *stack, int value)
{
	if (!stack)
		return -1;
	if (stack->ptr >= stack->capacity) {
		if (resize(stack, stack->capacity * 2))
			return -2;
	}
	stack->data[stack->ptr++] = value;

	return 0;
}

int pop(struct stack *stack, int *err)
{
	int res;

	if (!stack) {
		*err = -1;
		return 0;
	}
	
	res = stack->data[--stack->ptr];
	if (stack->ptr < stack->capacity / 4)
		resize(stack, stack->capacity / 2);
	*err = 0;
	return res;
}

void free_stack(struct stack *st)
{
	free(st->data);	
	free(st);
}

static struct stack *st;

static void catch_signal(int sign)
{
	printf("Freeing stack...\n");
	free_stack(st);
	exit(0);
}

int main(void)
{
	int err, res;
	char cmd[10];
	struct sigaction action;

	action.sa_handler = catch_signal;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	st = create_stack();
	if (!st) {
		printf("Can't create stack!\n");
		return -1;
	}

	if (sigaction(SIGINT, &action, NULL)) {
		printf("Can't catch signal :(\n");
		free_stack(st);
		return -1;
	}

	while (1) {
		scanf("%s", cmd);
		if (!strcmp(cmd, "-")) {
			res = pop(st, &err);
			if (err)
				printf("Error! Stack is empty\n");
			else
				printf("Value: %d\n", res);
		} else {
			res = atoi(cmd);
			err = push(st, res);
			if (err)
				printf("Failed to push!\n");
		}
		printf("Stack capacity: %d\n", st->capacity);
	}
	return 0;
}
