#include <stdio.h>

unsigned int hashFunction(int value) {
	return value ^ 0x1abcf;
}

void insert(int *arr, int size, int value) {
	if(!arr) return;
	int index = hashFunction(value);
	for(unsigned int i = 0; i < size; i++) {
		if(arr[(index+i)%size] == value) break;
		if(arr[(index+i)%size] == 0) {
			arr[(index+i)%size] = value;
			break;
		}
	}
}

int get(int *arr, int size, int value) {
	if(!arr) return -1;
	int index = hashFunction(value);
	for(unsigned int i = 0; i < size; i++) {
		if(arr[(index+i)%size] == value) return (index+i)%size;
		if(arr[(index+i)%size] == 0) return -1;
	}
	return -1;
}

#define ARR_SIZE 10

int main() {
	int arr[ARR_SIZE] = {0};
	insert(arr, ARR_SIZE, 1);
	insert(arr, ARR_SIZE, 3);
	insert(arr, ARR_SIZE, 2);
	insert(arr, ARR_SIZE, 8);
	insert(arr, ARR_SIZE, 6);
	insert(arr, ARR_SIZE, 9);
	insert(arr, ARR_SIZE, 2);
	insert(arr, ARR_SIZE, 13);
	for(unsigned int i = 0; i < ARR_SIZE; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	for(unsigned int i = 0; i < 16; i++) {
		printf("%d on index: %d \n", i+1, get(arr, ARR_SIZE, i+1));
	}
	return 0;
}
