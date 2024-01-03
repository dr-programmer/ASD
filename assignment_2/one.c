#include <stdio.h>
#include <stdlib.h>

struct Node {
	float value;
	struct Node *left;
	struct Node *right;
};

struct Node *createNode(float value) {
	struct Node *temp = (struct Node *)calloc(1, sizeof(struct Node));
	temp->value = value;
	return temp;
}

struct Node *push(struct Node *node, float value) {
	if(!node) return createNode(value);
	if(value < node->value) node->left = push(node->left, value);
	else node->right = push(node->right, value);
	return node;
}

int avgWeightPriv(struct Node *node, float *sum, int *div) {
	if(!node) return 0;
	int weight = avgWeightPriv(node->left, sum, div) + avgWeightPriv(node->right, sum, div);
	*div += weight;
	*sum += node->value * weight;
	return weight + 1;
}

float avgWeight(struct Node *node) {
	float sum = 0;
	int div = 0;
	avgWeightPriv(node, &sum, &div);
	return sum / div;
}

int main() {
	struct Node *root = NULL;
	root = push(root, 5);
	root = push(root, 1);
	root = push(root, 7);
	root = push(root, 3);
	root = push(root, 12);
	root->right->right->right = createNode(3.14);
	printf("Average weight: %f\n", avgWeight(root));
	return 0;
}
