#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void mergeSort(int *arr, size_t size) {
	if(size < 2) return;

	size_t center = size / 2;
	mergeSort(arr, center);
	mergeSort(arr + center, size - center);

	int i = 0, j = center;
	while(j < size) {
		if(arr[i] > arr[j]) {
			swap(arr + i, arr + j);
		}
		i++;
		if(i >= j) i = ++j - center;
	}
}

int main() {
	int arr[] = {420, 5, 12, -2, 69, 42};
	mergeSort(arr, 6);
	for(size_t i = 0; i < 6; i++) {
		printf("%d ", arr[i]);
	}

	return 0;
}
