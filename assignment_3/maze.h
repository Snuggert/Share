/* Contains function related to the maze map of the game. */

#ifndef MAZE_H
#define MAZE_H

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

#define WALL    '#'
#define START   'S'
#define EXIT    'E'

/* Incomplete type declaration. */
typedef struct 
{
	int width, height;
	int startX, startY;
	int endX, endY;
	char *map;
} maze_t;


/* Incomplete declarations of the support functions. */
maze_t *initMaze(int width, int height);
maze_t *readMaze(char* fileName);
void printMaze(maze_t* maze);
void cleanupMaze ();

#endif
