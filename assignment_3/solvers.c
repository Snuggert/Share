#include "maze.h"
#include "walker.h"
#include "solvers.h"

/* Will contain the definitions of the maze solver functions. */
void mySuperMazeSolverFunction(struct maze_t *maze, int **route) 
{
	int *intMaze, size, currentNumber, width, height;
	width = maze->width;
	height = maze->height;
	char *charMap = maze->map;
	size = map->height * map->width;
	intMaze = malloc(size);

	intMaze[maze->startY * maze->width + maze->startX] = 0;
	currentNumber = 0;

	while(1)
	{	
		for(int index = 0; index < size; index++)
		{
			if(intMaze[index] == currentNumber)
			{
				// fill north with the currentNumber + 1 if possible.
				if(intMaze[index-width] == -1 && charMap[index-width] == ' ')
				{
					intMaze[index-width] = currentNumber + 1;
				}
				// fill west with the currentNumber + 1 if possible.
				if(intMaze[index-1] == -1 && charMap[index-1] == ' ')
				{
					intMaze[index-1] = currentNumber - 1;
				}
				// fill south with the currentNumber + 1 if possible.
				if(intMaze[index+width] == -1 && charMap[index+width] == ' ')
				{
					intMaze[index+width] = currentNumber + 1;
				}
				// fill east with the currentNumber + 1 if possible.
				if(intMaze[index+1] == -1 && charMap[index+1] == ' ')
				{
					intMaze[index+1] = currentNumber + 1;
				}
			}
		}
		break;
	}
}

/* Next super solver here.. */
