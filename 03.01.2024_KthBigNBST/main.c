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

float largestKPriv(struct Node *node, int *k) {
	if(!node) return 0.5;
	float right = largestKPriv(node->right, k);
	if(--(*k) == 0) return node->value;
	float left = largestKPriv(node->left, k);
	if(right != 0.5) return right;
	else return left;
}

int largestK(struct Node *node, int k) {
	return largestKPriv(node, &k);
}

void printTabs(struct Node *node, int depth) {
	for(int i = 0; i < depth; i++) {
		printf("\t\b|");
	}
	printf("->[_%d_]- \n", node->value);
}

void printTreeB(struct Node *node, int depth) {
	if(!node) return;
	printTreeB(node->right, depth+1);
	printTabs(node, depth);
	printTreeB(node->left, depth+1);
}

int main() {
	struct Node *root = NULL;
	root = push(root, 6);
	root = push(root, 3);
	root = push(root, 8);
	root = push(root, 7);
	root = push(root, 10);
	root = push(root, 9);
	root = push(root, 16);
	root = push(root, 15);
	root = push(root, 14);
	root = push(root, 13);
	root = push(root, 11);
	root = push(root, 12);
	int k = 6;
	printTreeB(root, 0);
	printf("%d largest = %d \n", k, largestK(root, k));
	return 0;
}
