#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define LETTER_COUNT 32

void fillLetters(char *letters, char *str) {
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

void createNodes(struct Node *nodes[], char *letters) {
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
		if(current->next == NULL) break;
		struct Node *combined = createNode('*', current->node->num + current->next->node->num);
		combined->left = current->node;
		combined->right = current->next->node;
		current = current->next->next;
		current = pushList(current, combined);
	}
	return current->node;
}

unsigned int countNodes(struct Node *node) {
	if(!node) return 0;
	return 1 + countNodes(node->left) + countNodes(node->right);
}

unsigned int huffman(char *str) {
	if(!str) return 0;
	char letters[LETTER_COUNT] = {0};
	fillLetters(letters, str);
	struct Node *nodes[LETTER_COUNT] = {0};
	createNodes(nodes, letters);
	struct ListNode *list = createList(nodes);
	struct Node *tree = createTree(list);
	unsigned int count = countNodes(tree);
	return count;
}

unsigned int *second(char *str) {
	if(!str) return NULL;
	unsigned int *result = (unsigned int  *)calloc(26, sizeof(unsigned int));
	for(unsigned int i = 0; str[i] != '\0'; i++) {
		int temp = (str[i] - 'a') - i;
		if(temp < 0) temp = ('z' - 'a') + temp + 1;
		result[temp]++;
	}
	return result;
}

int main() {
	unsigned int first = huffman("alabala");
	printf("First = %d \n", first);
	unsigned int *arr = second("cbaa");
	for(unsigned int i = 0; i < 26; i++) {
		printf("%u ", arr[i]);
	}
	printf("\n");
	return 0;
}
