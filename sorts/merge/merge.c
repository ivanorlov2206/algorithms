#include <stdio.h>
#include <stdlib.h>


static int *tarr;

void merge(int *nums, int sp1, int ep1, int sp2, int ep2)
{
	int i;

	for (i = sp1; i <= ep2; i++)
		tarr[i] = nums[i];
	int p1 = sp1, p2 = sp2;
	int cp = p1;
	while (p1 <= ep1 || p2 <= ep2) {
		if (p1 > ep1)
			nums[cp++] = tarr[p2++];
		else if (p2 > ep2)
			nums[cp++] = tarr[p1++];
		else if (tarr[p1] <= tarr[p2])
			nums[cp++] = tarr[p1++];
		else
			nums[cp++] = tarr[p2++];
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

int main(void)
{
	int n, i;
	int *numbers;

	scanf("%d", &n);
	numbers = malloc(sizeof(int) * n);
	tarr = malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		scanf("%d", &numbers[i]);

	merge_sort(numbers, 0, n - 1);
	for (i = 0; i < n; i++)
		printf("%d ", numbers[i]);
	printf("\n");

	free(tarr);
	free(numbers);
}
