#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

struct stack_node {
	struct stack_node *next;
	int value;
};

struct stack {
	struct stack_node *first;
	int size;
};

struct stack *create_stack(void)
{
	struct stack *res = malloc(sizeof(*res));
	if (!res)
		return NULL;
	res->size = 0;
	res->first = NULL;
	return res;
}

int push(struct stack *stack, int value)
{
	struct stack_node *node;

	if (!stack)
		return -1;
	
	node = malloc(sizeof(*node));
	if (!node)
		return -2;

	node->value = value;
	node->next = stack->first;
	stack->first = node;

	return 0;
}

int pop(struct stack *stack, int *err)
{
	int res;
	struct stack_node *fn;

	if (!stack || !stack->first) {
		*err = -1;
		return 0;
	}
	res = stack->first->value;
	fn = stack->first;
	stack->first = stack->first->next;
	free(fn);
	*err = 0;
	return res;
}

void free_stack(struct stack *st)
{
	struct stack_node *cur = st->first;
	struct stack_node *next;
	while (cur) {
		next = cur->next;
		free(cur);
		cur = next;
	}
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
	}
	return 0;
}
