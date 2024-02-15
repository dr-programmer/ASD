#include <stdio.h>
#include <stdlib.h>

struct Edge {
	int weight;
	struct Node *node;
};

struct Node {
	int value;
	struct Edge *edges;
	size_t e_size;
};

struct Node *createNode(int value) {
	struct Node *temp = (struct Node *)calloc(1, sizeof(struct Node));
	temp->value = value;
	temp->e_size = 0;
	return temp;
}

void createBond(struct Node *node1, struct Node *node2) {
	if(!node1 || !node2) return;
	node1->e_size++;
	node1->edges = (struct Edge *)realloc(node1->edges, node1->e_size * sizeof(struct Edge));
	node2->e_size++;
	node2->edges = (struct Edge *)realloc(node2->edges, node2->e_size * sizeof(struct Edge));
	node1->edges[node1->e_size-1].node = node2;
	node2->edges[node2->e_size-1].node = node1;
}

struct Node *push(struct Node *node, int num) {
	if(!node) return createNode(num);
	struct Node *temp = createNode(num);
	createBond(node, temp);
	return temp;
}

void initNodeArr(struct Node *nodes[], size_t size) {
	for(int i = 0; i < size; i++) {
		nodes[i] = createNode(i+1);
	}
}

#define PRINT_BOND(NODE1, NODE2, I1, I2) printf("%d -> %d && %d -> %d \n", NODE1->value, \
			NODE1->edges[I1].node->value, \
			NODE2->value, \
			NODE2->edges[I2].node->value);

int main() {
	struct Node *nodes[10];
	initNodeArr(nodes, 10);
	createBond(nodes[0], nodes[1]);
	PRINT_BOND(nodes[0], nodes[1], 0, 0);
	struct Node *test = push(nodes[6], 11);
	PRINT_BOND(nodes[6], test, 0, 0);
	struct Node *doubleTest = push(nodes[0], 12);
	PRINT_BOND(nodes[0], doubleTest, 1, 0);
	return 0;
}
