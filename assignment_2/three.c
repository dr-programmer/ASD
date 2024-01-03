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

#define MAGIC_NUM 3.5

int heaviestPathPriv(struct Node *node, int line) {
	if(!node) return 0;
	if(!node->left && !node->right) return line + node->value;
	float left = MAGIC_NUM, right = MAGIC_NUM;
	if(node->left) left = heaviestPathPriv(node->left, line + node->value);
	if(node->right) right = heaviestPathPriv(node->right, line + node->value);
	if(left != MAGIC_NUM && (right == MAGIC_NUM || left > right)) return left;
	else return right;
}

int heaviestPath(struct Node *node) {
	return heaviestPathPriv(node, 0);
}

int main() {
	struct Node *root = NULL;
	root = createNode(5);
	root->left = createNode(4);
	root->right = createNode(8);
	root->left->left = createNode(11);
	root->right->left = createNode(13);
	root->right->right = createNode(4);
	root->left->left->left = createNode(7);
	root->left->left->right = createNode(2);
	root->right->right->right = createNode(1);
	printf("Heaviest path: %d \n", heaviestPath(root));
	return 0;
}
