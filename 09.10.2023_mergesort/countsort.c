#include <stdio.h>
#include <stdlib.h>

void countSort(int *arr, int min, int max, size_t size) {
	size_t temp_size = max - min + 1;
	int *temp = (int *)calloc(temp_size, sizeof(int));
	for(size_t i = 0; i < size; i++) {
		temp[arr[i] - min]++;
	}
	int j = 0;
	for(size_t i = 0; i < temp_size; i++) {
		while(1) {
			if(temp[i] == 0) break;
			arr[j] = i + min;
			i++;
			j++;
		}
	}
	free(temp);
}

int main() {
	int arr[] = {420, 5, 12, -2, 69, 42};
	countSort(arr, -5, 500, 6);
	for(size_t i = 0; i < 6; i++) {
		printf("%d ", arr[i]);
	}
	return 0;
}
