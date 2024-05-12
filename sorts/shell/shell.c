#include <stdio.h>
#include <stdlib.h>

void shell_sort(int n, int *nums)
{
	int i, j, t;

	int k = 1;
	while (k < n / 3) k = (k * 3) + 1;

	while (k > 0) {
		for (i = k; i < n; i++) {
			for (j = i; j >= k && nums[j] < nums[j - k]; j -= k) {
				t = nums[j];
				nums[j] = nums[j - k];
				nums[j - k] = t;
			}
		}
		k /= 3;
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

	shell_sort(n, numbers);
	for (i = 0; i < n; i++)
		printf("%d ", numbers[i]);
	printf("\n");

	free(numbers);
}
