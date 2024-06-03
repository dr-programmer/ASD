#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILE_NAME "file.txt"
#define MAX_ROW_SIZE 128
#define MAX_COLUMN_SIZE 128
#define MAX_NUM_OF_AGENTS 9

#define PRINT_HORIZONTAL_CANVAS(N) for(unsigned int i = 0; i < N; i++) { \
					if(i == 0 || i+1 == N) printf("|"); \
					else printf("-"); \
				   } \
				   printf("\n");

struct Coords {
	int x;
	int y;
};

struct Position {
	struct Coords current;
	struct Coords target;
	struct Position *par;
};

struct StepsList {
	struct Position *position;
	struct Path *next;
};

struct Position *createPosition(unsigned int currX, unsigned int currY, unsigned int tarX, unsigned int tarY) {
	struct Position *temp = (struct Position *)calloc(1, sizeof(struct Position));
	temp->current.x = currX;
	temp->current.y = currY;
	temp->target.x = tarX;
	temp->target.y = tarY;
	return temp;
}

struct Position **findAgents(char (*maze)[MAX_COLUMN_SIZE], unsigned int rows, unsigned int columns) {
	if(!maze) return NULL;
	struct Position **result = (struct Position **)calloc(MAX_NUM_OF_AGENTS, sizeof(struct Position *));
	struct Coords destinations[MAX_NUM_OF_AGENTS] = {0};
	for(unsigned int i = 0; i < rows; i++) {
		for(unsigned int j = 0; j < columns; j++) {
			if(maze[i][j] >= '1' && maze[i][j] <= '9') {
				result[maze[i][j] - '1'] = createPosition(i, j, 0, 0);
			}
			else if(maze[i][j] >= 'A' && maze[i][j] <= 'Z') {
				destinations[maze[i][j] - 'A'].x = i;
				destinations[maze[i][j] - 'A'].y = j;
			}
		}
	}
	for(unsigned int i = 0; i < MAX_NUM_OF_AGENTS; i++) {
		if(result[i] == NULL) continue;
		result[i]->target.x = destinations[i].x;
		result[i]->target.y = destinations[i].y;
	}
	return result;
}

#define PRINT_POSITION_STRUCT(POS) printf("x = %u, y - %u, tx = %u, ty = %u \n", POS->current.x, \
											POS->current.y, \
											POS->target.x, \
											POS->target.y); 

unsigned int heuristic(struct Coords current, struct Coords target) {
	unsigned int xLen = target.x - current.x;
	unsigned int yLen = target.y - current.y;
	return sqrt((xLen * xLen) + (yLen * yLen));
}

struct Coords *sortSteps(char (*maze)[MAX_COLUMN_SIZE], 
			unsigned int rows, 
			unsigned int columns, 
			struct Position *agent)
{
	if(!maze || !agent) return NULL;
	struct Coords *result = (struct Coords *)calloc(4, sizeof(struct Coords));
	int heuristics[5] = {-1, -1, -1, -1, -1}; // 0 - up; 1 - down; 2 - left; 3 - right; 4 - impossible
	if(agent->current.x > 0) 
		heuristics[0] = heuristic((struct Coords){agent->current.x-1, agent->current.y}, agent->target);
	if(agent->current.x+1 < rows) 
		heuristics[1] = heuristic((struct Coords){agent->current.x+1, agent->current.y}, agent->target);
	if(agent->current.y > 0) 
		heuristics[2] = heuristic((struct Coords){agent->current.x, agent->current.y-1}, agent->target);
	if(agent->current.y+1 < columns) 
		heuristics[3] = heuristic((struct Coords){agent->current.x, agent->current.y+1}, agent->target);

	unsigned int sortedStepsPattern[4] = {0, 1, 2, 3};
	for(unsigned int i = 0; i < 4; i++) {
		for(unsigned int j = 0; j < 3; j++) {
			if((heuristics[sortedStepsPattern[j]] == -1 
			|| heuristics[sortedStepsPattern[j]] > heuristics[sortedStepsPattern[j+1]])
			&& heuristics[sortedStepsPattern[j+1]] != -1) {
				//printf("Heuristic = %d \n", heuristics[sortedStepsPattern[j]]);
				if(heuristics[sortedStepsPattern[j]] == -1) {
					sortedStepsPattern[j] = 4;
				}
				unsigned int temp = sortedStepsPattern[j];
				sortedStepsPattern[j] = sortedStepsPattern[j+1];
				sortedStepsPattern[j+1] = temp;
			}
		}
	}

	for(unsigned int i = 0; i < 4; i++) {
		if(sortedStepsPattern[i] == 0) 
			result[i] = (struct Coords){agent->current.x-1, agent->current.y};
		else if(sortedStepsPattern[i] == 1)
			result[i] = (struct Coords){agent->current.x+1, agent->current.y};
		else if(sortedStepsPattern[i] == 2) 
			result[i] = (struct Coords){agent->current.x, agent->current.y-1};
		else if(sortedStepsPattern[i] == 3) 
			result[i] = (struct Coords){agent->current.x, agent->current.y+1};
		else result[i] = (struct Coords){-1, -1};
	}

	return result;
}

void findAgentPath(char (*maze)[MAX_COLUMN_SIZE], unsigned int rows, unsigned int columns, struct Position *agent) {
	if(!maze || !agent) return;
	struct Coords *steps = sortSteps(maze, rows, columns, agent);
	for(unsigned int i = 0; i < 4; i++) {
		printf("x = %d; y = %d; ", steps[i].x, steps[i].y);
	}
	printf("\n");
}

struct Coords *findPaths(char (*maze)[MAX_COLUMN_SIZE], unsigned int rows, unsigned int columns) {
	if(!maze) return NULL;
	struct Position **agents = findAgents(maze, rows, columns);

	for(unsigned int i = 0; i < MAX_NUM_OF_AGENTS; i++) {
		if(agents[i] == NULL) continue;
		//PRINT_POSITION_STRUCT(agents[i]);

		findAgentPath(maze, rows, columns, agents[i]);
	}

	return NULL;
}

void printMaze(char (*maze)[MAX_COLUMN_SIZE], unsigned int rows, unsigned int columns) {
	if(!maze) return;
	PRINT_HORIZONTAL_CANVAS(columns+2);
	for(unsigned int i = 0; i < rows; i++) {
		printf("|");
		for(unsigned int j = 0; j < columns; j++) {
			printf("%c", maze[i][j]);
		}
		printf("|\n");
	}
	PRINT_HORIZONTAL_CANVAS(columns+2);
}

int main() {
	FILE *file = fopen(FILE_NAME, "r");

	char row[MAX_ROW_SIZE] = {0};
	fgets(row, MAX_ROW_SIZE, file);
	unsigned int columns = strlen(row) - 3;

	char maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE] = {0};
	unsigned int rows;
	for(rows = 0;; rows++) {
		fgets(row, MAX_ROW_SIZE, file);
		if(row[1] == '-') break;
		for(unsigned int j = 1; j <= columns; j++) {
			maze[rows][j-1] = row[j];
		}
	}

	printMaze(maze, rows, columns);
	findPaths(maze, rows, columns);

	fclose(file);
	return 0;
}
