#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

unsigned int depth(struct Node *head) {
	if(!head) return 0;
	unsigned int left = depth(head->left), right = depth(head->right);
	return 1 + (left > right ? left : right);
}

struct Node *left(struct Node *node) {
	struct Node *right = node->right;
	node->right = right->left;
	right->left = node;
	return right;
}

struct Node *right(struct Node *node) {
	struct Node *left = node->left;
	node->left = left->right;
	left->right = node;
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

struct Node *balance(struct Node *head) {
	if(!head) return NULL;
	head->left = balance(head->left);
	head->right = balance(head->right);
	int leftD = depth(head->left);
	int rightD = depth(head->right);
	if(leftD != rightD && (leftD > 1 || rightD > 1)) {
		if(leftD > rightD) {
			if(head->left->left) head = right(head);
			else head = leftRight(head);
		}
		else {
			if(head->right->right) head = left(head);
			else head = rightLeft(head);
		}
	}
	return head;
}

void printTabs(unsigned int num, int value, int depth) {
	for(unsigned int i = 0; i < num; i++) {
		printf("\t\b|");
	}
	printf("->%d D: %d \n", value, depth);
}

void printTreeB(struct Node *node, int depth) {
	if(!node) return;
	printTreeB(node->right, depth+1);
	printTabs(depth, node->value, depth+1);
	printTreeB(node->left, depth+1);
}

int count(struct Node *head) {
	if(!head) return 0;
	return 1 + count(head->left) + count(head->right);
}

int isBalanced(struct Node *head, int depth, int height) {
	if(!head) {
		if(depth == height) return -1;
		else return 0;
	}
	int leftH = isBalanced(head->left, depth+1, height);
	int rightH = isBalanced(head->right, depth+1, height);
	if(leftH != rightH) return 0;
	return fmax(leftH, rightH) + 1;
}

int main() {
	struct Node *head = NULL;
	head = push(head, 6);
	head = push(head, 8);
	head = push(head, 1);
	head = push(head, 7);
	head = push(head, 2);
	head = push(head, 3);
	head = push(head, 2);
	head = push(head, 9);
	head = push(head, 3);
	head = push(head, 2);
	head = push(head, 3);
	head = push(head, 5);
	printf("Depth: %d \n", depth(head));
	printTreeB(head, 0);
	while(!isBalanced(head, 0, depth(head))) head = balance(head);
	//head = balance(head);
	//head = balance(head);
	//head = balance(head);
	printf("%d \n", count(head));
	printf("Is balanced: %d", isBalanced(head, 0, depth(head)));
	printf("\n\n\n");
	printTreeB(head, 0);
	return 0;
}
