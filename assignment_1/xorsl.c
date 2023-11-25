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

struct Node *applySkipPriv(struct Node *head, struct Node *prev) {
	if(head == NULL) return NULL;
	head->xorSkip = applySkipPriv(xor(head->xor, prev), head);
	if(prev) head->xorSkip = xor(head->xorSkip, xor(prev->xor, head));
	return xor(head->xor, prev);
}

struct Node *applySkip(struct Node *head) {
	return applySkipPriv(head, NULL);
}

struct Node *removeIndexPriv(struct Node *head, struct Node *prev, unsigned int index, unsigned int pos) {
	if(!head || index < pos) return NULL;
	struct Node *temp = NULL;
	if(index == pos) {
		temp = xor(head->xor, prev);
		if(prev) {
			struct Node *prevPrev = xor(prev->xor, head);
			prev->xor = xor(temp, prevPrev);
			struct Node *tempNext = xor(head->xorSkip, prevPrev);
			prev->xorSkip = xor(tempNext, xor(prev->xorSkip, temp));
			if(prevPrev) prevPrev->xorSkip = xor(temp, xor(prevPrev->xorSkip, head));
		}
		if(temp) {
			struct Node *tempNext = xor(temp->xor, head);
			temp->xor = xor(tempNext, prev);
			struct Node *prevPrev = xor(head->xorSkip, tempNext);
			temp->xorSkip = xor(xor(temp->xorSkip, prev), prevPrev);
			if(tempNext) tempNext->xorSkip = xor(xor(tempNext->xorSkip, head), prev);
		}
		free(head);
		return temp;
	}
	if(prev) temp = xor(prev->xor, head);
	temp = removeIndexPriv(xor(head->xorSkip, temp), xor(head->xor, prev), index, pos+2);
	if(!temp) removeIndexPriv(xor(head->xor, prev), head, index, pos+1);
	return head;
}

struct Node *removeIndex(struct Node *head, unsigned int index) {
	return removeIndexPriv(head, NULL, index, 0);
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

void checkSkip(struct Node *head, struct Node *prev) {
	struct Node *front, *prevTwo = NULL;
	while(head) {
		if(prevTwo)
			printf("%-3d <- ", prevTwo->value);
		else if(head->value < 0) printf("\t\b\b");
		else printf("\t\b");
		printf("%d", head->value);
		front = xor(head->xorSkip, prevTwo);
		if(front)
			printf(" -> %3d", front->value);
		if(front || prevTwo) printf("; ");
		prevTwo = prev;
		front = head;
		head = xor(head->xor, prev);
		prev = front;
		printf("\n");
	}
}

int main() {
	struct Node *head = NULL;
	head = insert(head, 3);
	head = insert(head, 6);
	head = insert(head, 8);
	head = insert(head, -8);
	head = insert(head, 0);
	head = insert(head, -1);
	head = insert(head, 69);
	head = insert(head, 23);
	head = insert(head, 5);
	head = insert(head, 9);
	head = insert(head, 2);
	head = insert(head, 1);
	printList(head);
	applySkip(head);
	checkSkip(head, NULL);
	head = removeIndex(head, 0);
	head = removeIndex(head, 3);
	head = removeIndex(head, 9);
	printList(head);
	checkSkip(head, NULL);
	return 0;
}
