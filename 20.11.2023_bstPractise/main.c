#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	struct Node *left;
	struct Node *right;
};

struct Node *createNode(int value) {
	struct Node *temp = (struct Node *)calloc(1, sizeof(struct Node));
	temp->value = value;
	return temp;
}

struct Node *push(struct Node *head, int value) {
	if(!head) return createNode(value);
	if(head->value > value) head->left = push(head->left, value);
	else head->right = push(head->right, value);
	return head;
}

int size(struct Node *head) {
	if(!head) return 0;
	else return 1 + size(head->left) + size(head->right);
}

int isBst(struct Node *head) {
	unsigned char check = 1;
	if(!head) return 1;
	if(head->left) check = head->value > head->left->value;
	if(head->right && check) check = head->value <= head->right->value;
	return check && isBst(head->left) && isBst(head->right);
}

int depth(struct Node *head) {
	if(!head) return 0;
	int left = depth(head->left), right = depth(head->right);
	if(left < right) left = right;
	return 1 + left;
}

int isBalanced(struct Node *head) {
	if(!head) return 0;
	int left = isBalanced(head->left), right = isBalanced(head->right);
	if(left - right > 1 || left - right < -1) return 0;
	if(left < right) left = right;
	return 1 + left;
}

int main() {
	struct Node *head = NULL;
	head = push(head, 6);
	head = push(head, 7);
	head = push(head, 3);
	head = push(head, 1);
	head = push(head, 8);
	head = push(head, 9);
	head = push(head, 7);
	printf("Size of BST: %d \n", size(head));
	printf("Is BST: %d \n", isBst(head));
	printf("Depth: %d \n", depth(head));
	printf("Is balanced: %d \n", isBalanced(head));
	return 0;
}
