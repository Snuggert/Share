#include "maze.h"

/* Incomplete definitions of the maze support function . */
maze_t *init_maze(int width, int height)
{
	return maze;
}

maze_t *read_maze(char *fileName)
{
	int width, height;
	char ch;
	maze_t *maze;
	FILE *filePointer = fopen(fileName,"r");
	if (filePointer == NULL)
	{
		perror("Error reading file");
		exit(EXIT_FAILURE);
	}
	
	ch = getc(filePointer);
	if()
	{

	}
    maze = init_maze()
    maze.map = malloc(10*10);
	return maze;
}

void print_maze(char *mapArray)
{

}

void cleanup_maze ()
{

}
