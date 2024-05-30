#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(int *nums, int lo, int hi)
{
	int i = lo, j = hi + 1;

	while (1) {
		while(nums[++i] < nums[lo] && i < hi);
		while(nums[--j] > nums[lo] && j > lo);
		if (i >= j)
			break;
		swap(&nums[i], &nums[j]);
	}
	swap(&nums[lo], &nums[j]);
	return j;
}

void quick_sort(int *nums, int start_pos, int end_pos)
{
	if (start_pos >= end_pos)
		return;
	int j = partition(nums, start_pos, end_pos);
	quick_sort(nums, start_pos, j - 1);
	quick_sort(nums, j + 1, end_pos);
}

int main(void)
{
	int n, i;
	int *numbers;

	scanf("%d", &n);
	numbers = malloc(sizeof(int) * n);

	for (i = 0; i < n; i++)
		scanf("%d", &numbers[i]);

	quick_sort(numbers, 0, n - 1);

	for (i = 0; i < n; i++)
		printf("%d ", numbers[i]);
	printf("\n");

	free(numbers);
}
