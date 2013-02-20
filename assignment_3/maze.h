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
	char *map;
} maze_t;


/* Incomplete declarations of the support functions. */
maze_t *init_maze(int width, int height);
maze_t *read_maze(char * fileName);
void print_maze(char *mapArray);
void cleanup_maze ();

#endif
