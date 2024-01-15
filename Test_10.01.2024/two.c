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

float small(struct Node *node, int num_neg) {
	if(!node) return 0;
	if(!node->left && !node->right) return node->value;
	int temp = num_neg;
	if(node->value < 0) temp++;
	float left = 0.5, right = 0.5;
	int num = (num_neg & 1) == 1 ? -1 : 1;
	printf("num = %d, %d node = %d\n", num_neg, num, node->value);
	if(node->left) left = small(node->left, temp) * node->value * num;
	if(node->right) right = small(node->right, temp) * node->value * num;
	if(left != 0.5 && (right == 0.5 || left < right)) return left;
	else return right;
}

int new(struct Node *node, int line) {
	printf("herei\n");
	if(!node) return 0;
	if(!node->left && !node->right) return node->value * line;
	float left = 0.5, right = 0.5;
	if(node->left) left = new(node->left, line * node->value);
	if(node->right) right = new(node->right, line * node->value);
	if(left != 0.5 && (right == 0.5 || left < right)) return left;
	else return right;
}

int smallest_product_to_leaf(struct Node *node) {
	return small(node, 0);
}

int main() {
	struct Node *root = NULL;
	root = push(root, 3);
	root = push(root, 2);
	root = push(root, -1);
	root = push(root, 4);
	root = push(root, 3);
	printf("%d \n", smallest_product_to_leaf(root));
	printf("%d \n", new(root, 1));
	return 0;
}
