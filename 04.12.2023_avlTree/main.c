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

struct Node *left(struct Node *node) {
	struct Node *right = node->right;
	node->right = right->left;
	right->left = node;
	node->height = node->left != NULL ? node->left->height + 1 : 1;
	int temp = right->right != NULL ? right->right->height : 0;
	right->height = node->height > temp ? node->height + 1 : temp + 1;
	return right;
}

struct Node *right(struct Node *node) {
	struct Node *left = node->left;
	node->left = left->right;
	left->right = node;
	node->height = node->right != NULL ? node->right->height + 1 : 1;
	int temp = left->left != NULL ? left->left->height : 0;
	left->height = node->height > temp ? node->height + 1 : temp + 1;
	return left;
}

struct Node *leftRight(struct Node *node) {
	node->left = left(node->left);
	return right(node);
}

struct Node *rightLeft(struct Node *node) {
	node->right = right(node->right);
	return left(node);
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
	int leftH = node->left != NULL ? node->left->height : 0;
	int rightH = node->right != NULL ? node->right->height : 0;
	if(leftH - rightH > 1) {
		if(node->left->left) node = right(node);
		else node = leftRight(node);
	}
	else if(rightH - leftH > 1) {
		if(node->right->right) node = left(node);
		else node = rightLeft(node);
	}
	return node;
}

void printTree(struct Node *node) {
	if(!node) return;
	printTree(node->left);
	printf("V: %d, H: %d; ", node->value, node->height);
	printTree(node->right);
}

void printTabs(unsigned int num, int value, int height) {
	for(unsigned int i = 0; i < num; i++) {
		printf("\t\b|");
	}
	printf("->%d H: %d \n", value, height);
}

void printTreeB(struct Node *node, int depth) {
	if(!node) return;
	printTreeB(node->right, depth+1);
	printTabs(depth, node->value, node->height);
	printTreeB(node->left, depth+1);
}

int main() {
	struct Node *head = NULL;
	head = push(head, 6);
	head = push(head, 5);
	head = push(head, 2);
	head = push(head, 3);
	head = push(head, 4);
	head = push(head, 5);
	head = push(head, 1);
	head = push(head, 3);
	head = push(head, 4);
	head = push(head, 7);
	head = push(head, 8);
	head = push(head, 3);
	head = push(head, -1);
	head = push(head, 10);
	head = push(head, 11);
	head = push(head, 9);
	head = push(head, 6);
	head = push(head, -3);
	head = push(head, 8);
	head = push(head, 33);
	printTreeB(head, 0);
	return 0;
}
