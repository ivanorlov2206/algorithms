#include <stdio.h>
#include <stdlib.h>

void selection_sort(int n, int *nums)
{
	int i, j, min, t;

	for (i = 0; i < n; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (nums[j] < nums[min])
				min = j;
		t = nums[i];
		nums[i] = nums[min];
		nums[min] = t;
	}
}

int main(void)
{
	int n, i;
	int *numbers;

	scanf("%d", &n);
	numbers = malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
		scanf("%d", &numbers[i]);

	selection_sort(n, numbers);
	for (i = 0; i < n; i++)
		printf("%d ", numbers[i]);
	printf("\n");

	free(numbers);
}
