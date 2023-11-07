#include <stdio.h>
#include <stdlib.h>

struct Node {
	struct Node *next;
	struct Node *twoNext;
	int value;
};

struct Node *createNode(int value) {
	struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
	temp->value = value;
	temp->next = NULL;
	temp->twoNext = NULL;
	return temp;
}

struct Node *insert(struct Node *head, int value) {
	if(!head) return createNode(value);
	else if(head->value >= value) {
		struct Node *temp = createNode(value);
		temp->next = head;
		return temp;
	}
	head->next = insert(head->next, value);
	return head;
}

struct Node *applySkip(struct Node *head) {
	if(!head->next) return head->next;
	head->twoNext = applySkip(head->next);
	return head->next;
}

void printList(struct Node *head) {
	while(head) {
		printf("%d ", head->value);
		head = head->next;
	}
	printf("\n");
}

void checkSkipConnections(struct Node *head) {
	while(head) {
		if(head->twoNext != NULL) printf("%d -> %d, ", head->value, head->twoNext->value);
		head = head->next;
	}
	printf("\n");
}

int contains(struct Node *head, int value) {
	if(head == NULL || head->value > value) return 0;
	else if(head->value == value) return 1;
	return contains(head->next, value) | contains(head->twoNext, value);
}

int main() {
	struct Node *head = NULL;
	head = insert(head, 1);
	head = insert(head, 3);
	head = insert(head, 2);
	head = insert(head, 6);
	printList(head);
	applySkip(head);
	checkSkipConnections(head);
	if(contains(head, 6)) printf("Contains!\n");
	if(contains(head, 7)) printf("Contains!\n");
	return 0;
}
