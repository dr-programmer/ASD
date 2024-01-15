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

int isFlourished(struct Node *node) {
	if(!node) return 1;
	if((node->left && node->right) || (!node->left && !node->right)) {
		return isFlourished(node->left) && isFlourished(node->right);
	}
	return 0;
}

int left_zigzag(struct Node *node);
int right_zigzag(struct Node *node);

int left_zigzag(struct Node *node) {
	if(!node) return 1;
	if(node->right) return 0;
	return right_zigzag(node->left);
}

int right_zigzag(struct Node *node) {
	if(!node) return 1;
	if(node->left) return 0;
	return left_zigzag(node->right);
}

int zigZag(struct Node *node) {
	return left_zigzag(node) && right_zigzag(node);
}

int main() {
	struct Node *root = NULL;
	root = push(root, 3);
	root = push(root, 4);
	root = push(root, 2);
	root = push(root, 5);
	root = push(root, 1);
	root = push(root, 2);
	//root = push(root, 3);
	printf("Is Flourished %d \n", isFlourished(root));
	return 0;
}
