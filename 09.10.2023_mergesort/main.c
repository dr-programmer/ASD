#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

size_t partition(int *arr, size_t size) {
	int pivot = arr[size / 2];
	size_t i = 0, j = size - 1;
	while(1) {
		while (arr[i] < pivot) i++;
		while (arr[j] > pivot) j--;
		if (i >= j) return i;
		swap(arr + i, arr + j);
	}
}

void quickSort(int *arr, size_t size) {
	if (size < 2) return;

	size_t pivot = partition(arr, size);
	quickSort(arr, pivot);
	quickSort(arr + pivot + 1, size - pivot - 1);
}

int main() {
	int arr[] = {420, 5, 12, -2, 69, 42};
	quickSort(arr, 6);
	for(size_t i = 0; i < 6; i++) {
		printf("%d ", arr[i]);
	}

	return 0;
}
