#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int n, int *nums)
{
	int i, j, t;

	for (i = 1; i < n; i++) {
		j = i;
		while(j > 0 && nums[j] < nums[j - 1]) {
			t = nums[j];
			nums[j] = nums[j - 1];
			nums[j - 1] = t;
			j--;
		}
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

	insertion_sort(n, numbers);
	for (i = 0; i < n; i++)
		printf("%d ", numbers[i]);
	printf("\n");

	free(numbers);
}
