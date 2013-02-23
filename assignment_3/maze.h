#ifndef MAZE_H
#define MAZE_H

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

#define WALL    '#'
#define START   'S'
#define EXIT    'E'

// Complete type declarations. 
struct maze_t
{
	int width, height;
	int startX, startY;
	int endX, endY;
	char *map;
};

struct walker_t;


// Complete declarations of the support functions.
struct maze_t *initMaze(int width, int height);
struct maze_t *readMaze(char* fileName);
void printMaze(struct maze_t* maze, struct walker_t* walker, int count);
void cleanupMaze(struct maze_t* maze);

#endif
