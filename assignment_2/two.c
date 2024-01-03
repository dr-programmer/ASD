#include <stdio.h>
#include <stdlib.h>

struct Node {
	char value;
	struct Node *left;
	struct Node *right;
};

struct Node *createNode(char value) {
	struct Node *temp = (struct Node *)calloc(1, sizeof(struct Node));
	temp->value = value;
	return temp;
}

struct Node *push(struct Node *node, char value) {
	if(!node) return createNode(value);
	if(value < node->value) node->left = push(node->left, value);
	else node->right = push(node->right, value);
	return node;
}

void charactersPriv(struct Node *node, char *arr) {
	if(!node) return;
	arr[node->value - 'a']++;
	charactersPriv(node->left, arr);
	charactersPriv(node->right, arr);
}

void printArray(char *arr) {
	for(int i = 'z' - 'a'; i >= 0; i--) {
		while(!arr[i]) i--;
		if(i >= 0) printf("%c -> %d; ", i + 'a', arr[i]);
	}
	printf("\n");
}

void characters(struct Node *node) {
	char arr[26] = {0};
	charactersPriv(node, arr);
	printArray(arr);
}

int main() {
	struct Node *root = NULL;
	root = push(root, 'v');
	root = push(root, 'g');
	root = push(root, 'z');
	root = push(root, 'a');
	root = push(root, 'j');
	root = push(root, 'v');
	root = push(root, 'a');
	root = push(root, 'k');
	root = push(root, 'x');
	root = push(root, 'a');
	characters(root);
	return 0;
}
