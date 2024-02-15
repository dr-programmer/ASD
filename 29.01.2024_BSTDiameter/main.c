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

struct Node *push(struct Node *node, int value) {
	if(!node) return createNode(value);
	if(value < node->value) node->left = push(node->left, value);
	else node->right = push(node->right, value);
	return node;
}

int _diameter(struct Node* node, int *result) {
	if(!node) return 0;
	int left = _diameter(node->left, result);
	int right = _diameter(node->right, result);
	int temp = left + right;
	if(*result < temp) *result = temp;
	if(left > right) return left + 1;
	else return right + 1;
}

int diameter(struct Node *node) {
	int result = 0;
	_diameter(node, &result);
	return result;
}

void printValue(int num, int tabs) {
	for(int i = 0; i < tabs; i++) {
		printf("\t\b|");
	}
	printf("->%d \n", num);
}

void printB(struct Node *node, int tabs) {
	if(!node) return;
	printB(node->right, tabs+1);
	printValue(node->value, tabs);
	printB(node->left, tabs+1);
}

int main() {
	struct Node *root = NULL;
	root = push(root, 6);
	root = push(root, 8);
	root = push(root, 0);
	root = push(root, 1);
	root = push(root, 2);
	root = push(root, 3);
	root = push(root, -3);
	root = push(root, -2);
	root = push(root, -1);
	root = push(root, -4);
	root = push(root, -5);
	root = push(root, -6);
	root = push(root, -7);
	root = push(root, -8);
	printB(root, 0);
	printf("The longest path from leaf to leaf is %d \n", diameter(root));
	return 0;
}
