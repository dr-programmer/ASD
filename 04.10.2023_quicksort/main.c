#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void quick_sort(int *arr, int start, int end) {
	if(start >= end) return;
	int pivot = arr[(start + end) / 2];
	int i = start, j = end;
	while(i <= j) {
		while(arr[i] < pivot) i++;
		while(arr[j] > pivot) j--;
		if(i <= j) {
			swap(&arr[i], &arr[j]);
			i++;
			j--;
		}
	}
	quick_sort(arr, start, j);
	quick_sort(arr, i, end);
}

int main() {
	int arr[] = {3, 1, 5, 6, 2, 9, 10};
	quick_sort(arr, 0, 6);
	for(int i = 0; i < 7; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}
