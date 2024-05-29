#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <err.h>
#include <math.h>

#define MAX_HEAP_SIZE 128
#define WIDE_K 3

struct max_heap {
	int *data;
	int size;
};

static void swap(int *a, int *b)
{
	int t;
	t = *a;
	*a = *b;
	*b = t;
}

static void heapify_down(struct max_heap *h, int v)
{
	int largest, left, right;
	while (v < h->size) {
		left = v * 2;
		right = v * 2 + 1;
		largest = v;

		if (left < h->size && h->data[left] > h->data[largest])
			largest = left;
		if (right < h->size && h->data[right] > h->data[largest])
			largest = right;
		if (largest != v) {
			swap(&h->data[v], &h->data[largest]);
			v = largest;
		} else {
			break;
		}
	}
}

static void heapify_up(struct max_heap *h, int v)
{
	int parent = v / 2;
	while (parent > 0 && h->data[parent] < h->data[v]) {
		swap(&h->data[v], &h->data[parent]);
		v = parent;
		parent = v / 2;
	}
}

static int add_element(struct max_heap *h, int x)
{
	h->data[h->size++] = x;
	heapify_up(h, h->size - 1);
}

static int remove_element(struct max_heap *h, int v)
{
	if (h->size == 1)
		return -1;
	swap(&h->data[v], &h->data[h->size--]);
	heapify_down(h, v);
}

static int get_maximum(struct max_heap *h)
{
	// Start counting with 1 to simplify index calculations
	if (h->size == 1)
		return INT_MIN;
	return h->data[1];
}

static void free_heap(struct max_heap *h)
{
	if (!h)
		return;
	free(h->data);
	free(h);
}

static void print_spaces(int cnt)
{
	int i;
	for (i = 0; i < cnt; i++)
		printf(" ");
}

static void print_heap(struct max_heap *h)
{
	int levels = (int)log2((h->size - 2) * 2);
	int sym_count = levels * WIDE_K * levels;
	int cur_ind = 1, i, j;

	for (i = 0; i <= levels; i++) {
		for (j = 0; j < (1 << i); j++) {
			if (cur_ind >= h->size)
				break;
			print_spaces(sym_count >> (i + 1));
			printf("%d", h->data[cur_ind++]);
			print_spaces(sym_count >> (i + 1));
		}
		printf("\n");
	}
	printf("\n");
}

int main(void)
{
	int n, i, tmp;
	struct max_heap *h;

	h = malloc(sizeof(*h));
	if (!h)
		err(1, "Failed to allocate a heap");
	h->data = malloc(sizeof(*h->data) * MAX_HEAP_SIZE);
	if (!h->data) {
		free(h);
		err(1, "Failed to allocate the data array");
	}
	h->size = 1;

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &tmp);
		add_element(h, tmp);
	}

	print_heap(h);

	int choice = 0;
	while (1) {
		scanf("%d", &choice);
		if (choice == 99)
			break;
		remove_element(h, choice);
		print_heap(h);
	};

	free_heap(h);


	return 0;
}
