#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int value;
	struct ListNode *next;
	struct ListNode *prev;
};

typedef struct {
	struct ListNode *head;
	size_t size;
} LinkedList;

struct ListNode *createNode(int value) {
	struct ListNode *temp = (struct ListNode *)malloc(sizeof(struct ListNode));
	temp->next = NULL;
	temp->value = value;
	return temp;
}

void pushFront(LinkedList *list, int value) {
	struct ListNode *temp = createNode(value);
	temp->next = list->head;
	list->head = temp;
	if(temp->next != NULL) temp->next->prev = list->head;
	list->size++;
}

void printList(LinkedList *list) {
	struct ListNode *temp = list->head;
	while(temp != NULL) {
		printf("%d ", temp->value);
		temp = temp->next;
	}
	printf("\n");
}

void mergeSort(struct ListNode **node) {
	if(*node == NULL || (*node)->next == NULL) return;

	struct ListNode *center = *node, *fast = *node;
	while(fast != NULL) {
		if(fast->next == NULL) break;
		fast = fast->next->next;
		if(fast != NULL) center = center->next;
	}
	struct ListNode *left = *node, *right = center->next;
	center->next = NULL;
	mergeSort(&left);
	mergeSort(&right);
	fast = NULL;
	*node = NULL;
	while(left != NULL && right != NULL) {
		if(left->value <= right->value) {
			*node = left;
			(*node)->prev = fast;
			if(left->next != NULL) {
				node = &((*node)->next);
				fast = left;
			}
			left = left->next;
		}
		else {
			*node = right;
			(*node)->prev = fast;
			if(right->next != NULL) {
				node = &((*node)->next);
				fast = right;
			}
			right = right->next;
		}
	}
	if(left != NULL) {
	       	(*node)->next = left;
		left->prev = *node;
	}
	else if(right != NULL) {
		(*node)->next = right;
		right->prev = *node;
	}
}

int main() {
	LinkedList list = {NULL, 0};
	pushFront(&list, 6);
	pushFront(&list, 7);
	pushFront(&list, 8);
	pushFront(&list, -2);
	pushFront(&list, 10);
	pushFront(&list, 5);
	mergeSort(&list.head);
	printf("%d \n", list.head->next->next->next->prev->value);
	printList(&list);
	return 0;
}
