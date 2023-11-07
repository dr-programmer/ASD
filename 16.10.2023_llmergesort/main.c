#include <stdio.h>
#include <stdlib.h>

struct Node {
	struct Node *next;
	struct Node *prev;
	int value;
};

struct Node *pushFront(struct Node *head, int value) {
	struct Node *temp = (struct Node *)calloc(1, sizeof(struct Node));
	temp->value = value;
	temp->next = head;
	if(head != NULL) head->prev = temp;
	return temp;
}

void printList(struct Node *head) {
	while(head != NULL) {
		printf("%d ", head->value);
		head = head->next;
	}
	printf("\n");
}

struct Node *middle(struct Node *head) {
	struct Node *fast = head, *slow = head;
	while(fast != NULL) {
		if(fast->next == NULL) break;
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

struct Node *merge(struct Node *head1, struct Node *head2) {
	if(head1 == NULL) return head2;
	else if(head2 == NULL) return head1;
	if(head1->value <= head2->value) {
		head1->next = merge(head1->next, head2);
		head1->next->prev = head1;
		return head1;
	}
	else {
		head2->next = merge(head1, head2->next);
		head2->next->prev = head2;
		return head2;
	}
}

struct Node *mergesort(struct Node *head) {
	if(head->next == NULL || head == NULL) return head;
	struct Node *center = middle(head);
	center->prev->next = NULL;
	head = mergesort(head);
	center = mergesort(center);
	struct Node *result = merge(head, center);
	return result;
}

struct Node *invert(struct Node *head, struct Node *prev) {
	if(head == NULL) return prev;
	struct Node *temp = invert(head->next, head);
	head->next = prev;
	return temp;
}

int isLooping(struct Node *head) {
	struct Node *slow = head, *fast = head;
	while(fast != NULL) {
		slow = slow->next;
		if(fast->next != NULL) fast = fast->next->next;
		else break;
		if(fast == slow || fast->next == slow) return 1;

	}
	return 0;
}

int isLoopingR(struct Node *head, struct Node *next) {
	if(next == NULL) return -1;
	else if(next->next == NULL) return -1;
	if(head == next || next->next == head) return 1;
	else return isLoopingR(head->next, next->next->next);
}

int main() {
	struct Node *head = NULL;
	head = pushFront(head, 6);
	head = pushFront(head, 7);
	head = pushFront(head, 8);
	head = pushFront(head, 10);
	head = pushFront(head, 13);
	head = mergesort(head);
	printList(head);
	head = invert(head, NULL);
	printList(head);
	head->next->next->next = head;
	int check = isLooping(head);
	if(check) printf("%d \n", check);
	int checkR = isLoopingR(head, head->next);
	if(check) printf("%d \n", checkR);
	return 0;
}
