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
	if(node->value < value) node->left = push(node->left, value);
	else node->right = push(node->right, value);
	return node;
}

int isIdentical(struct Node *node1, struct Node *node2) {
	if(!node1 && !node2) return 1;
	if(!node1 || !node2) return 0;
	if(node1->value == node2->value) 
		return isIdentical(node1->left, node2->left) && isIdentical(node1->right, node2->right);
	return 0;
}

int subTree(struct Node *node1, struct Node *node2) {
	if(!node2) return 1;
	if(!node1) return 0;
	if(node1->value == node2->value) return isIdentical(node1, node2);
	return subTree(node1->left, node2) || subTree(node1->right, node2);
}

int main() {
	struct Node *head = NULL;
	head = push(head, 3);
	head = push(head, 4);
	head = push(head, 2);
	head = push(head, 9);
	head = push(head, 5);
	head = push(head, 8);
	//head = push(head, 10);
	struct Node *new = NULL;
	new = push(new, 9);
	new = push(new, 8);
	if(subTree(head, new)) printf("Subtree!\n");
	if(isIdentical(head, new)) printf("Identical\n");
	return 0;
}
