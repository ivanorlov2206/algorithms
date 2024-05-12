#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

struct queue_node {
	struct queue_node *next;
	int value;
};

struct queue {
	struct queue_node *first;
	struct queue_node *last;
	int size;
};

struct queue *create_queue(void)
{
	struct queue *res = malloc(sizeof(*res));
	if (!res)
		return NULL;
	res->size = 0;
	res->first = NULL;
	res->last = NULL;
	return res;
}

int enqueue(struct queue *queue, int value)
{
	struct queue_node *node;

	if (!queue)
		return -1;
	
	node = malloc(sizeof(*node));
	if (!node)
		return -2;

	node->value = value;
	node->next = NULL;
	if (queue->last)
		queue->last->next = node;
	queue->last = node;
	if (!queue->first)
		queue->first = node;

	return 0;
}

int dequeue(struct queue *queue, int *err)
{
	int res;
	struct queue_node *fn;

	if (!queue || !queue->first) {
		*err = -1;
		return 0;
	}
	res = queue->first->value;
	fn = queue->first;
	queue->first = queue->first->next;
	free(fn);
	*err = 0;
	return res;
}

void free_queue(struct queue *st)
{
	struct queue_node *cur = st->first;
	struct queue_node *next;
	while (cur) {
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(st);
}

static struct queue *q;

static void catch_signal(int sign)
{
	printf("Freeing queue...\n");
	free_queue(q);
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

	q = create_queue();
	if (!q) {
		printf("Can't create queue!\n");
		return -1;
	}

	if (sigaction(SIGINT, &action, NULL)) {
		printf("Can't catch signal :(\n");
		free_queue(q);
		return -1;
	}

	while (1) {
		scanf("%s", cmd);
		if (!strcmp(cmd, "-")) {
			res = dequeue(q, &err);
			if (err)
				printf("Error! queue is empty\n");
			else
				printf("Value: %d\n", res);
		} else {
			res = atoi(cmd);
			err = enqueue(q, res);
			if (err)
				printf("Failed to push!\n");
		}
	}
	return 0;
}
