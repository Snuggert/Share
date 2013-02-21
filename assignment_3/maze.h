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
struct maze_t
{
	int width, height;
	int startX, startY;
	int endX, endY;
	char *map;
};

struct walker_t;


/* Incomplete declarations of the support functions. */
struct maze_t *initMaze(int width, int height);
struct maze_t *readMaze(char* fileName);
void printMaze(struct maze_t* maze);
void cleanupMaze ();

#endif
