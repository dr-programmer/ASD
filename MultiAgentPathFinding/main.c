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
	struct StepsList *next;
};

struct Position *createPosition(unsigned int currX, unsigned int currY, unsigned int tarX, unsigned int tarY) {
	struct Position *temp = (struct Position *)calloc(1, sizeof(struct Position));
	temp->current.x = currX;
	temp->current.y = currY;
	temp->target.x = tarX;
	temp->target.y = tarY;
	return temp;
}

struct StepsList *createStepsList(struct Position *pos, struct Position *par) {
	struct StepsList *temp = (struct StepsList *)calloc(1, sizeof(struct StepsList));
	temp->position = pos;
	if(temp->position) temp->position->par = par;
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

struct StepsList *pushStep(struct StepsList *list, struct Position *position, struct Position *par) {
	if(!list) return createStepsList(position, par);
	list->next = pushStep(list->next, position, par);
	return list;
}

struct StepsList *pushSteps(struct StepsList *list, 
			char (*maze)[MAX_COLUMN_SIZE], 
			unsigned int rows, 
			unsigned int columns, 
			struct Position *agent)
{
	if(!maze || !agent) return NULL;

	if(agent->current.x > 0 && maze[agent->current.x-1][agent->current.y] != '#' 
	&& maze[agent->current.x-1][agent->current.y] != maze[agent->current.x][agent->current.y]) {
		list = pushStep(list, 
				createPosition(agent->current.x-1, 
						agent->current.y, 
						agent->target.x, 
						agent->target.y), 
				agent);
		maze[agent->current.x-1][agent->current.y] = maze[agent->current.x][agent->current.y];
	}
	if(agent->current.x+1 < rows && maze[agent->current.x+1][agent->current.y] != '#' 
	&& maze[agent->current.x+1][agent->current.y] != maze[agent->current.x][agent->current.y]) {
		list = pushStep(list, 
				createPosition(agent->current.x+1, 
						agent->current.y, 
						agent->target.x, 
						agent->target.y), 
				agent);
		maze[agent->current.x+1][agent->current.y] = maze[agent->current.x][agent->current.y];
	}
	if(agent->current.y > 0 && maze[agent->current.x][agent->current.y-1] != '#' 
	&& maze[agent->current.x][agent->current.y-1] != maze[agent->current.x][agent->current.y]) {
		list = pushStep(list, 
				createPosition(agent->current.x, 
						agent->current.y-1, 
						agent->target.x, 
						agent->target.y), 
				agent);
		maze[agent->current.x][agent->current.y-1] = maze[agent->current.x][agent->current.y];
	}
	if(agent->current.y+1 < columns && maze[agent->current.x][agent->current.y+1] != '#' 
	&& maze[agent->current.x][agent->current.y+1] != maze[agent->current.x][agent->current.y]) {
		list = pushStep(list, 
				createPosition(agent->current.x, 
						agent->current.y+1, 
						agent->target.x, 
						agent->target.y), 
				agent);
		maze[agent->current.x][agent->current.y+1] = maze[agent->current.x][agent->current.y];
	}

	return list;
}

struct Position *findAgentPath(char (*maze)[MAX_COLUMN_SIZE], 
				unsigned int rows, 
				unsigned int columns, 
				struct Position *agent)
{
	if(!maze || !agent) return NULL;
	if(agent->current.x == agent->target.x && agent->current.y == agent->target.y) return agent;
	struct StepsList *list = NULL;
	list = pushSteps(list, maze, rows, columns, agent);
	struct Position *result = NULL;
	while(list) {
		list = pushSteps(list, maze, rows, columns, list->position);
		if(list->position->current.x == agent->target.x && list->position->current.y == agent->target.y) {
			result = list->position;
			break;
		}
		list = list->next;
	}
	return result;
}

struct Position **findPaths(char (*maze)[MAX_COLUMN_SIZE], unsigned int rows, unsigned int columns) {
	if(!maze) return NULL;
	struct Position **agents = findAgents(maze, rows, columns);

	struct Position **results = (struct Position **)calloc(MAX_NUM_OF_AGENTS, sizeof(struct Position));

	for(unsigned int i = 0; i < MAX_NUM_OF_AGENTS; i++) {
		if(agents[i] == NULL) continue;
		//PRINT_POSITION_STRUCT(agents[i]);
		maze[agents[i]->current.x][agents[i]->current.y] = '1' + i;
		struct Position *result = findAgentPath(maze, rows, columns, agents[i]);
		results[i] = result;
	}

	return results;
}

void copyMaze(char (*oMaze)[MAX_COLUMN_SIZE], char (*nMaze)[MAX_COLUMN_SIZE]) {
	if(!oMaze) return;
	for(unsigned int i = 0; i < MAX_ROW_SIZE; i++) {
		for(unsigned int j = 0; j < MAX_COLUMN_SIZE; j++) {
			nMaze[i][j] = oMaze[i][j];
		}
	}
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

void printPaths(struct Position **results, char (*maze)[MAX_COLUMN_SIZE], unsigned int rows, unsigned int columns) {
	if(!results) return;
	for(unsigned int i = 0; i < MAX_NUM_OF_AGENTS; i++) {
		char tMaze[MAX_ROW_SIZE][MAX_COLUMN_SIZE] = {0};
		copyMaze(maze, tMaze);
		struct Position *temp = results[i];
		if(temp == NULL) continue;
		while(temp) {
			tMaze[temp->current.x][temp->current.y] = '1' + i;
			temp = temp->par;
		}
		printMaze(tMaze, rows, columns);
	}
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
	char tempMaze[MAX_ROW_SIZE][MAX_COLUMN_SIZE] = {0};
	copyMaze(maze, tempMaze);

	struct Position **results = findPaths(tempMaze, rows, columns);
	printPaths(results, maze, rows, columns);

	printMaze(tempMaze, rows, columns);

	fclose(file);
	return 0;
}
