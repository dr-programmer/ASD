#include <stdio.h>
#include <stdlib.h>

struct Node {
	char row;
	char column;
	struct Node *left;
	struct Node *center;
	struct Node *right;
};

struct Node *createNode(int row, int column) {
	struct Node *temp = (struct Node *)calloc(1, sizeof(struct Node));
	temp->row = row;
	temp->column = column;
	return temp;
}

struct Node *pushTree(int row, int column, struct Node *node) {
	
}

struct Node *createTree(int **m, int rows, int columns, int cr, int cc, struct Node *node) {
	if(cr >= rows || cc >= columns) return NULL;
	if(m[cr][cc] == 1) return NULL;
	pushTree(cr, cc, node);
	createTree(m, rows, columns, cr+1, cc, node);
	createTree(m, rows, columns, cr, cc+1, node);
	createTree(m, rows, columns, cr-1, cc, node);
	createTree(m, rows, columns, cr, cc-1, node);
}

#define ROWS 3
#define COLUMNS 5

int main() {
	int m[ROWS][COLUMNS] = {
		{0, 0, 0, 1, 1},
		{1, 0, 0, 0, 0},
		{1, 1, 0, 1, 0}
	};
	struct Node *tree = NULL;
	tree = createTree(m, ROWS, COLUMNS, 0, 0, tree);
	return 0;
}
