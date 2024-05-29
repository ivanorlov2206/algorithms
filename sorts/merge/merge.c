#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

static int *tarr;

void merge(int *nums, int sp1, int ep1, int sp2, int ep2)
{
	int i;

	for (i = sp1; i <= ep2; i++)
		tarr[i] = nums[i];
	int p1 = sp1, p2 = sp2;
	for (i = p1; i <= ep2; i++) {
		if (p1 > ep1)
			nums[i] = tarr[p2++];
		else if (p2 > ep2)
			nums[i] = tarr[p1++];
		else if (tarr[p1] <= tarr[p2])
			nums[i] = tarr[p1++];
		else
			nums[i] = tarr[p2++];
	}
}

void merge_sort(int *nums, int start_pos, int end_pos)
{
	int m = (start_pos + end_pos) / 2;
	if (start_pos >= end_pos)
		return;
	merge_sort(nums, start_pos, m);
	merge_sort(nums, m + 1, end_pos);
	merge(nums, start_pos, m, m + 1, end_pos);
}

void bottom_up_merge_sort(int *nums, int n)
{
	int s, i;

	for (s = 1; s < n; s *= 2) {
		for (i = 0; i < n - s; i += 2 * s)
			merge(nums, i, i + s - 1, i + s, min(i + 2 * s - 1, n - 1));
	}
}

int main(void)
{
	int n, i;
	int *numbers, *numbers_bottom_up;

	scanf("%d", &n);
	numbers = malloc(sizeof(int) * n);
	tarr = malloc(sizeof(int) * n);

	numbers_bottom_up = malloc(sizeof(int) * n);

	for (i = 0; i < n; i++)
		scanf("%d", &numbers[i]);

	memcpy(numbers_bottom_up, numbers, sizeof(int) * n);

	merge_sort(numbers, 0, n - 1);
	bottom_up_merge_sort(numbers_bottom_up, n);

	for (i = 0; i < n; i++)
		printf("%d ", numbers[i]);
	printf("\n");

	for (i = 0; i < n; i++)
		printf("%d ", numbers_bottom_up[i]);
	printf("\n");

	free(tarr);
	free(numbers);
}
