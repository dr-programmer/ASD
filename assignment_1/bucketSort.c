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

void bucketSort(int *arr, int size, int min, int max) {
	int range = (max - min) / size;
	struct Node *buckets[size];
	for(int i = 0; i < size; i++) {
		buckets[i] = NULL;
	}
	for(int i = 0; i < size; i++) {
		int index = arr[i] / range;
		printf("Here - %d \n", index);
		//if(arr[i] == max && (max - min) <= (2 * max)) index--;
		printf("Here - %d \n", index);
		index -= min / range;
		printf("Here - %d -> %d \n", arr[i], index);
		if(index >= size) index = size-1;
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
	int arr[] = {69, 15, 1, -13, 23, -12, 3, 56};
	printArray(arr, 8);
	bucketSort(arr, 8, -13, 69);
	printArray(arr, 8);
	return 0;
}
