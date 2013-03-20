/*
 * File: solvers.c
 * 
 * This file contains different kinds of algorithms to solve a maze.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 23-02-2013
 */

#include "stdlib.h"

#include "maze.h"
#include "solvers.h"

/* Will contain the definitions of the maze solver functions. */
int mySuperMazeSolverFunction(maze_t *maze) 
{
	int size, currentNumber, currentPosition, width, height, heightIndex, 
		widthIndex;
	width = maze->ncols;
	height = maze->nrows;
	size = width * height;

	// init a map with the same dimensions as the charmap.
	int **intMaze = malloc(height * sizeof(*int));
	for(heightIndex = 0; heightIndex < height; heightIndex++)
	{
		intMaze[height] = malloc(width * sizeof(int))
	}

	// set all values in the intMap to 
	for(heightIndex = 0; heightIndex < height; heightIndex++)
	{
		for(widthIndex = 0; widthIndex < width; widthIndex++)
		{
			intMaze[height][width] = -1;
		}
	}

	// start position is set to 0
	intMaze[maze->start_row][maze->start_col] = 0;
	currentNumber = 0;

	while(currentNumber < size)
	{	
		// if currentnumber is located at the exit of the maze break the filling.
		if(intMaze[maze->exit_row][maze->exit_col] == currentNumber)
		{
			break;
		}
		for(heightIndex = 0; heightIndex < height; heightIndex++)
		{
			for(widthIndex = 0; widthIndex < width; widthIndex++)
			{
				if(intMaze[heightIndex][widthIndex] == currentNumber)
				{
					// fill north with the currentNumber + 1 if possible.
					if(intMaze[heightIndex-1][widthIndex] == -1 && 
						(maze->map[heightIndex-1][widthIndex] == ' ' || 
							maze->map[heightIndex-1][widthIndex] == 'E'))
					{
						intMaze[heightIndex-1][widthIndex] = currentNumber + 1;
					}
					// fill east with the currentNumber + 1 if possible.
					if(intMaze[heightIndex][widthIndex-1] == -1 && 
						(maze->map[heightIndex][widthIndex-1] == ' ' || 
							maze->map[heightIndex][widthIndex-1] == 'E'))
					{
						intMaze[heightIndex][widthIndex-1] = currentNumber + 1;
					}
					// fill south with the currentNumber + 1 if possible.
					if(intMaze[heightIndex+1][widthIndex] == -1 && 
						(maze->map[heightIndex+1][widthIndex] == ' ' || 
							maze->map[heightIndex+1][widthIndex] == 'E'))
					{
						intMaze[heightIndex+1][widthIndex] = currentNumber + 1;
					}
					// fill west with the currentNumber + 1 if possible.
					if(intMaze[heightIndex-1][widthIndex] == -1 && 
						(maze->map[heightIndex-1][widthIndex] == ' ' || 
							maze->map[heightIndex-1][widthIndex] == 'E'))
					{
						intMaze[heightIndex-1][widthIndex] = currentNumber + 1;
					}
				}
			}
		}
		currentNumber ++;
	}
	// if the currentNumber gets to be size, no exit is found and 0 is returned.
	if(currentNumber == size)
	{
		return 0;
	}
	currentPosition = maze->endY * width + maze->endX;
	*route = malloc((currentNumber) * sizeof(int));

	// fill the route from back to front with directions.
	for(int routeIndex = currentNumber - 1; routeIndex >= 0; routeIndex--)
	{
		// if the position NORTH of the current position is the number
		// currentPosition - 1 the move of routeIndex = SOUTH
		if(intMaze[currentPosition - width] == routeIndex)
		{
			(*route)[routeIndex] = SOUTH;
			currentPosition -= width;
		}

		// if the position EAST of the current position is the number
		// currentPosition - 1 the move of routeIndex = WEST
		else if(intMaze[currentPosition + 1] == routeIndex)
		{
			(*route)[routeIndex] = WEST;
			currentPosition += 1;
		}

		// if the position SOUTH of the current position is the number
		// currentPosition - 1 the move of routeIndex = NORTH
		else if(intMaze[currentPosition + width] == routeIndex)
		{
			(*route)[routeIndex] = NORTH;
			currentPosition += width;
		}

		// if the position WEST of the current position is the number
		// currentPosition - 1 the move of routeIndex = EAST
		else if(intMaze[currentPosition - 1] == routeIndex)
		{
			(*route)[routeIndex] = EAST;
			currentPosition -= 1;
		}
	}
	// exit was found.
	return currentNumber;
}