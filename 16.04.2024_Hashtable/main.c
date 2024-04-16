#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	struct Node *next;
};

struct Node *createNode(int value) {
	struct Node *temp = (struct Node *)calloc(1, sizeof(struct Node));
	temp->value = value;
	return temp;
}

struct Node *push(struct Node *node, int value) {
	struct Node *temp = createNode(value);
	temp->next = node;
	return temp;
}

unsigned int hashFunction(int number, int size) {
	return number % size;
}

void insertHashTable(struct Node *arr[], int size, int value) {
	if(!arr) return;
	unsigned int index = hashFunction(value, size);
	arr[index] = push(arr[index], value);
}

int getValue(struct Node *arr[], int size, int value) {
	if(!arr) return -1;
	unsigned int index = hashFunction(value, size);
	struct Node *temp = arr[index];
	while(temp) {
		if(temp->value == value) return index;
		temp = temp->next;
	}
	return -1;
}

#define ARR_SIZE 10

int main() {
	struct Node *arr[ARR_SIZE] = {0};
	insertHashTable(arr, ARR_SIZE, 1);
	insertHashTable(arr, ARR_SIZE, 2);
	insertHashTable(arr, ARR_SIZE, 3);
	insertHashTable(arr, ARR_SIZE, 8);
	insertHashTable(arr, ARR_SIZE, 9);
	insertHashTable(arr, ARR_SIZE, 16);
	for(unsigned int i = 1; i <= 16; i++) {
		printf("%d on index: %d \n", i, getValue(arr, ARR_SIZE, i));
	}
	return 0;
}
