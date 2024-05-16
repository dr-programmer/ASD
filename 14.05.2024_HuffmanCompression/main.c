#include <stdio.h>
#include <stdlib.h>

struct Node {
	char value;
	int num;
	struct Node *left;
	struct Node *right;
};

struct ListNode {
	struct Node *node;
	struct ListNode *next;
};

#define ARR_SIZE 128
#define LETTER_COUNT 32

void fillLetters(char *letters, const char * const str) {
	if(!letters || !str) return;
	for(unsigned int i = 0; str[i] != '\0'; i++) {
		letters[str[i]-'a']++;
	}
}

struct Node *createNode(char value, int num) {
	struct Node *temp = (struct Node *)calloc(1, sizeof(struct Node));
	temp->value = value;
	temp->num = num;
	return temp;
}

void createNodes(struct Node *nodes[], const char * const letters) {
	if(!nodes || !letters) return;
	for(unsigned int i = 0; i < LETTER_COUNT; i++) {
		if(letters[i] == 0) continue;
		nodes[i] = (struct Node *)calloc(1, sizeof(struct Node));
		nodes[i]->value = i + 'a';
		nodes[i]->num = letters[i];
	}
}

struct ListNode *createListNode(struct Node *node) {
	struct ListNode *listNode = (struct ListNode *)calloc(1, sizeof(struct ListNode));
	listNode->node = node;
	return listNode;
}

struct ListNode *pushList(struct ListNode *list, struct Node *node) {
	if(!node) return NULL;
	if(!list) return createListNode(node);
	if(list->node->num > node->num) {
		struct ListNode *temp = createListNode(node);
		temp->next = list;
		return temp;
	}
	list->next = pushList(list->next, node);
	return list;
}

struct ListNode *createList(struct Node *nodes[]) {
	if(!nodes) return NULL;
	struct ListNode *head = NULL;
	for(unsigned int i = 0; i < LETTER_COUNT; i++) {
		if(nodes[i]) head = pushList(head, nodes[i]);
	}
	return head;
}

struct Node *createTree(struct ListNode *list) {
	if(!list) return NULL;
	struct ListNode *current = list;
	while(current) {
		//printf("current->node->value = %c \n", current->node->value);
		if(current->next == NULL) break;
		struct Node *combined = createNode('*', current->node->num + current->next->node->num);
		combined->left = current->node;
		combined->right = current->next->node;
		current = current->next->next;
		current = pushList(current, combined);
	}
	return current->node;
}

unsigned int createCode(const char value, struct Node *tree) {
	if(!tree) return -1;
	if(tree->value == value) return 0;
	unsigned int leftCode = createCode(value, tree->left);
	unsigned int rightCode = createCode(value, tree->right);
	if(leftCode != -1) return (leftCode << 1) | 1;
	if(rightCode != -1) return rightCode << 1;
	return -1;
}

unsigned int *compress(const char * const str, struct Node *tree) {
	if(!str || !tree) return NULL;
	unsigned int *numbers = (unsigned int *)calloc(LETTER_COUNT, sizeof(unsigned int));
	unsigned int i;
	for(i = 0; str[i] != '\0'; i++) {
		numbers[i] = createCode(str[i], tree);
	}
	numbers[i] = -1;
	return numbers;
}

struct Node *huffmanTree = NULL;

unsigned int *huffman(const char * const str) {
	if(!str) return NULL;
	char letters[LETTER_COUNT] = {0};
	fillLetters(letters, str);
	struct Node *nodes[LETTER_COUNT] = {0};
	createNodes(nodes, letters);
	struct ListNode *list = createList(nodes);
	struct Node *tree = createTree(list);
	huffmanTree = tree;
	unsigned int *numbers = compress(str, tree);
	return numbers;
}

char *huffmanDecompress(const unsigned int * const compressed, struct Node *tree) {
	if(!compressed || !tree) return NULL;
	char *decompressed = (char *)calloc(ARR_SIZE, sizeof(char));
	struct Node *tempTree = tree;
	unsigned int i;
	for(i = 0; compressed[i] != -1; i++) {
		unsigned int number = compressed[i];
		unsigned int current = number & 1;
		while(tempTree->value == '*') {
			printf("%d", current);
			//printf("tempTree->value = %c \n", tempTree->value);
			number >>= 1;
			if(current) tempTree = tempTree->left;
			else tempTree = tempTree->right;
			current = number & 1;
		}
		printf("\n");
		decompressed[i] = tempTree->value;
		tempTree = tree;
	}
	decompressed[i] = '\0';
	return decompressed;
}

void printTabs(struct Node *node, int depth) {
	for(int i = 0; i < depth; i++) {
		printf("\t\b|");
	}
	printf("->[_%c_]- \n", node->value);
}

void printTreeB(struct Node *node, int depth) {
	if(!node) return;
	printTreeB(node->right, depth+1);
	printTabs(node, depth);
	printTreeB(node->left, depth+1);
}

int main() {
	char text[ARR_SIZE] = "alabalaportokala";
	//puts(text);
	unsigned int *compressed = huffman(text);
	for(unsigned int i = 0; compressed[i] != -1; i++) {
		printf("Code = %d \n", compressed[i]);
	}
	char *decompressed = huffmanDecompress(compressed, huffmanTree);
	printTreeB(huffmanTree, 0);
	puts(decompressed);
	return 0;
}
