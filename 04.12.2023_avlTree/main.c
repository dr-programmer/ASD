#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	int height;
	struct Node *left;
	struct Node *right;
};

struct Node *createNode(int value) {
	struct Node *temp = (struct Node *)calloc(1, sizeof(struct Node));
	temp->value = value;
	temp->height = 1;
	return temp;
}

struct Node *push(struct Node *node, int value) {
	if(!node) return createNode(value);
	int height;
	if(node->value > value) {
		node->left = push(node->left, value);
		height = node->left->height + 1;
	}
	else {
		node->right = push(node->right, value);
		height = node->right->height + 1;
	}
	node->height = height > node->height ? height : node->height;
	return node;
}

void printTree(struct Node *node) {
	if(!node) return;
	printTree(node->left);
	printf("V: %d, H: %d; ", node->value, node->height);
	printTree(node->right);
}

int main() {
	struct Node *head = NULL;
	head = push(head, 6);
	head = push(head, 3);
	head = push(head, 5);
	head = push(head, 4);
	head = push(head, 1);
	head = push(head, 7);
	head = push(head, 6);
	head = push(head, 10);
	printTree(head);
	return 0;
}
