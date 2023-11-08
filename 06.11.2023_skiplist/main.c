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
	if(!head->next) return NULL;
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
	return contains(head->twoNext, value) || contains(head->next, value);
}

struct Node *deleteIndexPriv(struct Node *head, int index, int position) {
	if(head == NULL) return head;
	if(index < position) return NULL;
	struct Node *temp;
	if(position == index) {
		temp = head->next;
		free(head);
		return temp;
	}
	temp = deleteIndexPriv(head->twoNext, index, position+2);
	if(temp == NULL) {
		temp = deleteIndexPriv(head->next, index, position+1);
		head->next = temp;
		if(temp) head->twoNext = temp->next;
		else head->twoNext = NULL;
		return head;
	}
	else {
		head->twoNext = temp;
		head->next->next = temp;
		head->next->twoNext = temp->next;
		return head;
	}
}

struct Node *deleteIndex(struct Node *head, int index) {
	return deleteIndexPriv(head, index, 0);
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
	head = deleteIndex(head, 1);
	checkSkipConnections(head);
	printList(head);
	return 0;
}
