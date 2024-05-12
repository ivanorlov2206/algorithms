#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

struct queue {
	int *data;
	size_t tail;
	size_t count;
	size_t capacity;
};

struct queue *create_queue(void)
{
	struct queue *res = malloc(sizeof(*res));
	if (!res)
		return NULL;
	res->capacity = 2;
	res->data = malloc(sizeof(int) * res->capacity);
	if (!res->data) {
		free(res);
		return NULL;
	}
	res->count = 0;
	res->tail = 0;
	return res;
}

int resize(struct queue *queue, int new_size)
{
	int i, st;
	int *new_data = malloc(sizeof(int) * new_size);

	if (!new_data)
		return -1;
	st = (queue->capacity + queue->tail - queue->count) % queue->capacity;
	for (i = 0; i < queue->count; i++) {
		new_data[i] = queue->data[st];
		st = (st + 1) % queue->capacity;
	}
	free(queue->data);
	queue->data = new_data;
	queue->capacity = new_size;
	queue->tail = queue->count;
	return 0;
}

int enqueue(struct queue *queue, int value)
{
	struct queue_node *node;

	if (!queue)
		return -1;
	
	if (queue->count == queue->capacity) {
		if (resize(queue, queue->capacity * 2))
			return -1;
	}
	queue->data[queue->tail] = value;
	queue->count++;
	queue->tail = (queue->tail + 1) % queue->capacity;

	return 0;
}

int dequeue(struct queue *queue, int *err)
{
	int res, pos;
	struct queue_node *fn;

	if (!queue || !queue->count) {
		*err = -1;
		return 0;
	}

	pos = (queue->capacity + queue->tail - queue->count) % queue->capacity;
	res = queue->data[pos];
	queue->count--;
	*err = 0;
	
	return res;
}

void free_queue(struct queue *q)
{
	free(q->data);
	free(q);
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
		printf("Capacity: %zu\n", q->capacity);
	}
	return 0;
}
