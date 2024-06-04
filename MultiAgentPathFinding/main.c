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

	unsigned int stepsLeft;
	unsigned int waitTime;
	unsigned int stepsToHere;
	unsigned short dangerous;
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
		if(list->position->current.x == agent->target.x && list->position->current.y == agent->target.y) {
			result = list->position;
			break;
		}
		list = pushSteps(list, maze, rows, columns, list->position);
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

unsigned int getPrime(unsigned int n) {
	if(n <= 1) return 2 + n;
	else if(n <= 3) return 5 + (n - 2) * 2;
	else if(n == 4) return 11;
	else return 6 * n - 1;
}

unsigned int *getFactors(unsigned int n) {
	unsigned int *result = (unsigned int *)calloc(MAX_NUM_OF_AGENTS, sizeof(unsigned int));
	unsigned int index = 0;
	for(unsigned int i = 0; n > 1; i++) {
		unsigned int prime = getPrime(i);
		if(index == 0 && n == prime) break;
		if(n % prime == 0) {
			result[index++] = prime;
			n /= prime;
		}
	}
	return result;
}

unsigned int getAgentIndex(unsigned int prime) {
	if(prime <= 3) return prime - 2;
	else if(prime <= 7) return (prime - 5) / 2 + 2;
	else if(prime == 11) return 4;
	else return (prime + 1) / 6;
}

struct Position *getPosition(struct Position *pos, unsigned int x, unsigned int y) {
	if(!pos) return NULL;
	struct Position *temp = pos, *result = NULL;
	unsigned int stepsToHere = 0;
	while(temp) {
		if(temp->current.x == x && temp->current.y == y) result = temp;
		else if(result) {
			stepsToHere += 1 + temp->waitTime;
		}
		else temp->waitTime = 0;
		temp = temp->par;
	}
	result->stepsToHere = stepsToHere;
	return result;
}

struct StepsList *createStepsListWithoutPar(struct Position *pos) {
	struct StepsList *temp = (struct StepsList *)calloc(1, sizeof(struct Position));
	temp->position = pos;
	return temp;
}

struct StepsList *pushByStepsLeft(struct StepsList *list, struct Position *pos) {
	if(!list) return createStepsListWithoutPar(pos);
	if(list->position->stepsLeft < pos->stepsLeft) {
		struct StepsList *temp = createStepsListWithoutPar(pos);
		temp->next = list;
		return temp;
	}
	list->next = pushByStepsLeft(list->next, pos);
	return list;
}

void addWait(struct Position **paths, unsigned int *factors, unsigned int x, unsigned int y) {
	if(!paths || !factors) return;
	struct StepsList *list = NULL;
	for(unsigned int i = 0; factors[i] != 0; i++) {
		unsigned int agentIndex = getAgentIndex(factors[i]);
		struct Position *intersection = getPosition(paths[agentIndex], x, y);
		list = pushByStepsLeft(list, intersection);
		if(agentIndex == 4)
		printf("wait agent %u: %u pos: %u, %u \n", agentIndex + 1, intersection->stepsToHere, 
								x, y);
	}
	if(!list) return;
	struct StepsList *originalList = list, *par = list;
	list = list->next;
	while(list) {
		int waitTime = par->position->stepsToHere - list->position->stepsToHere + 1;
		if(list->position->par && list->position->par->dangerous) list->position->par->waitTime = 0;
		else if(waitTime > 0 && list->position->par) list->position->par->waitTime += waitTime;
		else if(list->position->par && waitTime + list->position->par->waitTime <= 0) 
			list->position->par->waitTime = 0;
		par = list;
		list = list->next;
	}
	if(originalList->position->par) originalList->position->par->waitTime = 0;

	while(originalList) {
		struct StepsList *next = originalList->next;
		free(originalList);
		originalList = next;
	}
}

struct Position *pushCopyPosition(struct Position *head, struct Position *pos) {
	if(!head) {
		struct Position *temp = createPosition(pos->current.x, pos->current.y, pos->target.x, pos->target.y);
		temp->waitTime = pos->waitTime;
		temp->stepsToHere = pos->stepsToHere;
		temp->stepsLeft = pos->stepsLeft;
		return temp;
	}
	head->par = pushCopyPosition(head->par, pos);
	return head;
}

struct Position *orientPath(struct Position *pos) {
	if(!pos) return NULL;
	struct Position *result = orientPath(pos->par);
	result = pushCopyPosition(result, pos);
	return result;
}

unsigned short safe = 1;

unsigned int addDanger(struct Position *agent, unsigned int (*maze)[MAX_COLUMN_SIZE], unsigned int agentIndex) {
	if(!agent) return 0;
	//printf("Agent = %u \n", agentIndex);
	unsigned int found = addDanger(agent->par, maze, agentIndex);
	if(!found && maze[agent->current.x][agent->current.y] != getPrime(agentIndex)) {
		agent->dangerous = 1;
		if(agent->current.x == agent->target.x && agent->current.y == agent->target.y) {
			safe = 0;
		}
	}
	else return 1;
	return 0;
}

void findPathIntersections(struct Position **paths, 
				unsigned int rows, 
				unsigned int columns, 
				char (*oMaze)[MAX_COLUMN_SIZE])
{
	if(!paths) return;
	unsigned int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE] = {0};
	for(unsigned int i = 0; i < MAX_NUM_OF_AGENTS; i++) {
		if(paths[i] == NULL) continue;
		struct Position *temp = paths[i];
		for(unsigned int stepsLeft = 0; temp; stepsLeft++) {
			if(maze[temp->current.x][temp->current.y] == 0) 
				maze[temp->current.x][temp->current.y] = getPrime(i);
			else maze[temp->current.x][temp->current.y] *= getPrime(i);
			temp->stepsLeft = stepsLeft;
			temp = temp->par;
		}
	}
	for(unsigned int i = 0; i < rows; i++) {
		for(unsigned int j = 0; j < columns; j++) {
			printf("%-5u ", maze[i][j]);/*
			if(maze[i][j] != 0) {
				unsigned int *factors = getFactors(maze[i][j]);
				addWait(paths, factors, i, j);
			}*/
		}
		printf("\n");
	}

	struct Position **orientedPaths = (struct Position **)calloc(MAX_NUM_OF_AGENTS, sizeof(struct Position *));
	struct Position **tempOPs = (struct Position **)calloc(MAX_NUM_OF_AGENTS, sizeof(struct Position *));
	for(unsigned int i = 0; i < MAX_NUM_OF_AGENTS; i++) {
		orientedPaths[i] = orientPath(paths[i]);
		tempOPs[i] = orientedPaths[i];
	}
	unsigned short loop = 1, first = 1;
	while(loop) {
		loop = 0;
		for(unsigned int i = 0; i < MAX_NUM_OF_AGENTS; i++) {
			struct Position *pos = tempOPs[i];
			if(pos == NULL) continue;
			else loop = 1;
			unsigned int value = maze[pos->current.x][pos->current.y];
			if(value != 0) {
				if(first && getPrime(i) != maze[pos->current.x][pos->current.y]) { 
					addDanger(paths[i], maze, i);
					if(!safe) {
						
						safe = 1;
					}
				}
				unsigned int *factors = getFactors(value);
				addWait(paths, factors, pos->current.x, pos->current.y);
			}
			tempOPs[i] = tempOPs[i]->par;
			//printf("Here %d \n", i + 1);
		}
		first = 0;
	}
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
	if(!results || !maze) return;
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

void printSteps(struct Position **paths, char (*maze)[MAX_COLUMN_SIZE], unsigned int rows, unsigned int columns) {
	if(!paths || !maze) return;
	char tMaze[MAX_ROW_SIZE][MAX_COLUMN_SIZE] = {0};
	copyMaze(maze, tMaze);
	struct Position **tempPaths = (struct Position **)calloc(MAX_NUM_OF_AGENTS, sizeof(struct Position *));
	for(unsigned int i = 0; i < MAX_NUM_OF_AGENTS; i++) {
		tempPaths[i] = orientPath(paths[i]);
	}
	unsigned int time = 0;
	unsigned short loop = 1;
	while(1) {
		copyMaze(maze, tMaze);
		loop = 0;
		for(unsigned int i = 0; i < MAX_NUM_OF_AGENTS; i++) {
			struct Position *pos = tempPaths[i];
			if(pos == NULL) continue;
			else loop = 1;
			tMaze[pos->current.x][pos->current.y] = '1' + i;
			if(pos->waitTime > 0) pos->waitTime--;
			else tempPaths[i] = tempPaths[i]->par;
		}
		if(!loop) break;
		printf("Time: %u s \n", time++);
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

	findPathIntersections(results, rows, columns, maze);

	printSteps(results, maze, rows, columns);

	fclose(file);
	return 0;
}
