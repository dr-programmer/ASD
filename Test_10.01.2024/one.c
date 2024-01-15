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

int is_branch(struct Node *node) {
	if(!node) return 1;
	if(node->left && node->right) return 0;
	int left = is_branch(node->left);
	int right = is_branch(node->right);
	return left < right ? left : right;
}

int main() {
	struct Node *root = NULL;
	root = push(root, 3);
	root = push(root, 2);
	root = push(root, -1);
	root = push(root, 1);
	//root = push(root, -3);
	printf("Is branch = %d \n", is_branch(root));
	return 0;
}
