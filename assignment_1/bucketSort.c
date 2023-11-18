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

struct Node *insert(struct Node *head, int value) {
	if(head == NULL) return createNode(value);
	if(head->value >= value) {
		struct Node *temp = createNode(value);
		temp->next = head;
		return temp;
	}
	head->next = insert(head->next, value);
	return head;
}

void printList(struct Node *head) {
	while(head) {
		printf("%d ", head->value);
		head = head->next;
	}
	printf("\n");
}

void bucketSort(int *arr, int size, int max) {
	unsigned int range = max / size;
	struct Node *buckets[size];
	for(int i = 0; i < size; i++) {
		buckets[i] = NULL;
	}
	for(int i = 0; i < size; i++) {
		unsigned int index = arr[i] / range;
		if(arr[i] == max) index--;
		buckets[index] = insert(buckets[index], arr[i]);
		printList(buckets[index]);
	}
	struct Node *temp = NULL;
	for(int i = 0, j = 0; i < size; i++) {
		while(temp == NULL) temp = buckets[j++];
		arr[i] = temp->value;
		temp = temp->next;
	}
}

void printArray(int *arr, int size) {
	for(int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main() {
	int arr[] = {69, 15, 1, 13, 25, 12, 3, 26};
	printArray(arr, 8);
	bucketSort(arr, 8, 69);
	printArray(arr, 8);
	return 0;
}
