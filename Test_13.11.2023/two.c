#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void arange(int *arr, int size) {
	int arr1[size];
	int arr2[size];
	int size1 = 0, size2 = 0;
	for(int i = 0; i < size; i++) {
		if(!(arr[i] & 1)) {
			arr1[size1] = arr[i];
			size1++;
		}
		else {
			arr2[size2] = arr[i];
			size2++;
		}
	}
	sort_even_before_odd(arr1, 0, size1-1);
	sort_even_before_odd(arr2, 0, size2-1);
	for(int i = 0; i < size; i++) {
		if(i < size1) {
			arr[i] = arr1[i];
		}
		else {
			arr[i] = arr2[i-size1];
		}
	}
}

void sort_even_before_odd(int *arr, int start, int end) {
	if(start >= end) return;
	int pivot = arr[(start + end) / 2];
	int i = start, j = end;
	while(i <= j) {
		if(!(pivot & 1)) {
			while(arr[i] < pivot) i++;
			while(arr[j] > pivot) j--;
			if(i <= j) {
				swap(arr+i, arr+j);
				i++;
				j--;
			}
		}
		else {
			while(arr[i] > pivot) i++;
			while(arr[j] < pivot) j--;
			if(i <= j) {
				swap(arr+i, arr+j);
				i++;
				j--;
			}
		}
	}
	sort_even_before_odd(arr, start, j);
	sort_even_before_odd(arr, i, end);
}

int main() {
	int arr[] = {3, 2, 1, 10, 4, 5, 6};
	arange(arr, 7);
	for(int i = 0; i < 7; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}
