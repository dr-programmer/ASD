#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	struct Node *xor;
	struct Node *xorSkip;
};

struct Node *xor(struct Node *a, struct Node *b) {
	return (struct Node *)((size_t)a ^ (size_t)b);
}

struct Node *createNode(int value) {
	struct Node *temp = (struct Node *)calloc(1, sizeof(struct Node));
	temp->value = value;
	return temp;
}

struct Node *insertPriv(struct Node *head, struct Node *prev, int value) {
	if(!head) return createNode(value);
	if(head->value >= value) {
		struct Node *temp = createNode(value);
		head->xor = xor(xor(head->xor, prev), temp);
		temp->xor = head;
		return temp;
	}
	struct Node *temp = insertPriv(xor(head->xor, prev), head, value);
	temp->xor = xor(temp->xor, head);
	head->xor = temp;
	return head;
}

struct Node *insert(struct Node *head, int value) {
	return insertPriv(head, NULL, value);
}

void applySkipPriv(struct Node *head, struct Node *prev, int value) {

}

void applySkip(struct Node *head, int value) {
	applySkipPriv(head, NULL, value);
}

void printList(struct Node *head) {
	struct Node *prev = NULL, *temp;
	while(head) {
		printf("%d ", head->value);
		temp = head;
		head = xor(head->xor, prev);
		prev = temp;
	}
	printf("\n");
}

int main() {
	struct Node *head = NULL;
	head = insert(head, 3);
	head = insert(head, 6);
	head = insert(head, 8);
	printList(head);
	return 0;
}
