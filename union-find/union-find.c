#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

struct union_find {
	int *id;
	int *w;
	int n;
};

static struct union_find *create_union_find(int n)
{
	size_t i;
	struct union_find *res = malloc(sizeof(*res));
	if (!res)
		  return NULL;

	res->n = n;
	res->id = malloc(sizeof(int) * n);
	if (!res->id)
		goto free_res;
	res->w = malloc(sizeof(int) * n);
	if (!res->w)
		goto free_ids;

	for (i = 0; i < n; i++) {
		res->id[i] = i;
		res->w[i] = 1;
	}

	goto success;
free_ids:
	free(res->id);
free_res:
	free(res);
success:
	return res;
}

static int find_root(struct union_find *uf, int x)
{
	while (x != uf->id[x]) {
		// Compress the tree
		uf->id[x] = uf->id[uf->id[x]];
		x = uf->id[x];
	}
	return x;
}

static void un(struct union_find *uf, int p, int q)
{
	int root_p = find_root(uf, p);
	int root_q = find_root(uf, q);

	if (uf->w[root_p] < uf->w[root_q]) {
		uf->id[root_p] = root_q;
		uf->w[root_q] + uf->w[root_p];
	} else {
		uf->id[root_q] = root_p;
		uf->w[root_p] += uf->w[root_q];
	}
}

static bool find(struct union_find *uf, int p, int q)
{
	return find_root(uf, p) == find_root(uf, q);
}

static void free_union_find(struct union_find *uf)
{
	free(uf->id);
	free(uf->w);
	free(uf);
}

static struct union_find *uf;

static void catch_signal(int sign)
{
	printf("Freeing union-find...\n");
	free_union_find(uf);
	exit(0);
}

int main(void)
{
	char command;
	int p, q;

	struct sigaction action;

	action.sa_handler = catch_signal;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	uf = create_union_find(10);
	if (!uf) {
		printf("Can't create union_find\n");
		return -1;
	}

	if (sigaction(SIGINT, &action, NULL)) {
		printf("Can't catch signal :(\n");
		free_union_find(uf);
		return -1;
	}

	while (true) {
		scanf("%c %d %d", &command, &p, &q);
		switch (command) {
		case 'u':
			un(uf, p, q);
			break;
		case 'f':
			printf("Connected: %d\n", find(uf, p, q));
			break;
		}
	}

	return 0;
}
