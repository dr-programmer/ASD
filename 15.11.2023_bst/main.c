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
	if(node->value > value) node->left = push(node->left, value);
	else node->right = push(node->right, value);
	return node;
}

void printTree(struct Node *node) {
	if(!node) {
		printf("\n");
		return;
	}
	printf("%d ", node->value);
	printTree(node->left);
	printTree(node->right);
}

unsigned int isLooping(struct Node *node, struct Node *fast) {
	if(!node || !fast) return 0;
	int value = 0;
	struct Node *temp = fast->left;
	if(node == temp) return 1;
	if(temp) value += isLooping(node->left, temp->left);
	temp = fast->right;
	if(temp) value += isLooping(node->right, temp->right);
	return value;
}

int main() {
	struct Node *head = NULL;
	head = push(head, 3);
	head = push(head, 6);
	head = push(head, 7);
	head = push(head, 1);
	head = push(head, 2);
	printTree(head);
	head->left->left = head;
	if(isLooping(head, head)) printf("Loop\n");
	return 0;
}
