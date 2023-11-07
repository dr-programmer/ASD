#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	struct Node *xor;
};

struct Node *xor(struct Node *a, struct Node *b) {
	return (struct Node *)((size_t)a ^ (size_t)b);
}

struct Node *createNode(int value) {
	struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
	temp->value = value;
	temp->xor = NULL;
	return temp;
}

struct Node *pushFront(struct Node *head, int value) {
	struct Node *temp = createNode(value);
	head->xor = xor(temp, head->xor);
	temp->xor = head;
	return temp;
}

void printList(struct Node *head) {
	struct Node *temp = head, *prev = NULL;
	while(temp) {
		printf("%d ", temp->value);
		head = temp;
		temp = xor(temp->xor, prev);
		prev = head;
	}
	printf("\n");
}

unsigned short containsRec(struct Node *head, struct Node *prev, int value) {
	if(head == NULL) return 0;
	if(head->value == value) return 1;
	else return containsRec(xor(head->xor, prev), head, value);
}

unsigned short containsIter(struct Node *head, struct Node *prev, int value) {
	while(head) {
		if(head->value == value) return 1;
		struct Node *temp = head;
		head = xor(head->xor, prev);
		prev = temp;
	}
	return 0;
}

struct Node *findCenter(struct Node *head, struct Node *prev) {
	struct Node *slow = head, *slowPrev = prev;
	while(head) {
		struct Node *temp = xor(head->xor, prev);
		prev = head;
		if(temp) {
			head = xor(temp->xor, prev);
			prev = temp;
		}
		else break;
		if(head) {
			temp = slow;
			slow = xor(slow->xor, slowPrev);
			slowPrev = temp;
		}
	}
	struct Node *result = xor(slow->xor, slowPrev);
	result->xor = xor(result->xor, slow);
	slow->xor = slowPrev;
	return result;
}

struct Node *merge(struct Node *head1, struct Node *head1Prev, 
				struct Node *head2, 
				struct Node *head2Prev)
{
	if(head1 == NULL) {
		head2->xor = xor(head2->xor, head2Prev);
		return head2;
	}
	else if(head2 == NULL) {
		head1->xor = xor(head1->xor, head1Prev);
		return head1;
	}
	struct Node *next, *result;
	if(head1->value <= head2->value) {
		next = xor(head1->xor, head1Prev);
		result = merge(next, head1, head2, head2Prev);
		result->xor = xor(result->xor, head1);
		head1->xor = result;
		return head1;
	}
	else {
		next = xor(head2->xor, head2Prev);
		result = merge(next, head2, head1, head1Prev);
		result->xor = xor(result->xor, head2);
		head2->xor = result;
		return head2;
	}
}

static struct Node *mergeSortPriv(struct Node *head, struct Node *prev) {
	if(head == NULL || xor(head->xor, prev) == NULL) return head;
	struct Node *center = findCenter(head, prev);
	head = mergeSortPriv(head, NULL);
	printList(head);
	center = mergeSortPriv(center, NULL);
	printList(center);
	struct Node *result = merge(head, NULL, center, NULL);
	return result;
}

struct Node *mergeSort(struct Node *head) {
	return mergeSortPriv(head, NULL);
}

struct Node *popFront(struct Node *head) {
	if(head == NULL) return NULL;
	struct Node *temp = head->xor;
	if(temp) temp->xor = xor(temp->xor, head);
	free(head);
	return temp;
}

struct Node *freeList(struct Node *head) {
	if(head == NULL) return head;
	head = popFront(head);
	printList(head);
	return freeList(head);
}

int main() {
	struct Node *head = createNode(9);
	head = pushFront(head, 6);
	head = pushFront(head, 7);
	head = pushFront(head, 8);
	head = pushFront(head, -1);
	head = pushFront(head, 3);
	head = pushFront(head, 8);
	printList(head);
	if(containsRec(head, NULL, 6)) printf("Has R\n");
	if(containsIter(head, NULL, 6)) printf("Has I\n");
	head = mergeSort(head);
	printList(head);
	head = popFront(head);
	head = popFront(head);
	printList(head);
	head = freeList(head);
	return 0;
}
