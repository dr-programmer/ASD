#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	struct Node *next;
	struct Node *prev;
	struct Node *nextSort;
	struct Node *prevSort;
};

struct Node *createNode(int value) {
	struct Node *temp = (struct Node *)calloc(1, sizeof(struct Node));
	temp->value = value;
	return temp;
}

struct Node *pushFront(struct Node *head, int value) {
	struct Node *temp = createNode(value);
	if(head) head->prev = temp;
	temp->next = head;
	struct Node *check = temp, *checkBack = temp;
	while(head) {
		if(head->value >= check->value) {
			check = head;
		}
		else if(head->value < check->value) {
			checkBack = head;
		}
		head = head->next;
	}
	temp->nextSort = check;
	check->prevSort = temp;
	temp->prevSort = checkBack;
	checkBack->nextSort = temp;
	return temp;
}

void printAsAdded(struct Node *head) {
	while(head) {
		printf("%d ", head->value);
		head = head->next;
	}
	printf("\n");
}

void printAsSorted(struct Node *head) {
	//while(head) {
	//	head = head->prevSort;
	//}
	while(head) {
		printf("%d ", head->value);
		head = head->nextSort;
	}
	printf("\n");
}

int main() {
	struct Node *head = NULL;
	head = pushFront(head, 1);
	head = pushFront(head, 3);
	head = pushFront(head, 6);
	head = pushFront(head, 7);
	head = pushFront(head, 0);
	printAsAdded(head);
	//printAsSorted(head);
	return 0;
}
