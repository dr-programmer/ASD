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

#define V_SIZE 10

int isVisited(struct Node *visited[], struct Node *node) {
	int i;
	for(i = 0; i < V_SIZE; i++) {
		if(visited[i] == node) return -1;
		if(visited[i] == NULL) break;
	}
	return i;
}

void printGraph(struct Node *node, struct Node *visited[]) {
	if(!node) return;
	int index = isVisited(visited, node);
	if(index == -1) return;
	printf("%d ", node->value);
	visited[index] = node;
	for(int i = 0; i < node->e_size; i++) {
		printGraph(node->edges[i].node, visited);
	}
}

void printBfs(struct Node *node, struct Node *visited[]) {
	if(!node) return;
	int index = isVisited(visited, node);
	if(index != -1) visited[index] = node;
	for(int i = 1;; i++) {
		printf("%d \n", node->value);
		for(int j = 0; j < node->e_size; j++) {
			index = isVisited(visited, node->edges[j].node);
			//printf("Index = %d ;", index);
			if(index != -1) visited[index] = node->edges[j].node;
		}
		//printf("LOOP %d\n", node->value);
		node = visited[i];
		if(!node) break;
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
	createBond(nodes[0], nodes[2]);
	createBond(nodes[0], nodes[3]);
	createBond(nodes[1], nodes[4]);
	createBond(nodes[2], nodes[4]);
	createBond(nodes[3], nodes[5]);
	createBond(nodes[5], nodes[4]);
	struct Node *visited[V_SIZE] = {0};
	//printGraph(nodes[0], visited);
	printBfs(nodes[0], visited);
	return 0;
}
