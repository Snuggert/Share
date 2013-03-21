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
#include "solver.h"

/* Will contain the definitions of the maze solver functions. */
int breadthFirst(maze_t *maze) 
{
	int size, currentNumber, width, height, heightIndex, widthIndex, 
		start_row, start_col;
	width = maze->ncols;
	height = maze->nrows;
	size = width * height;

	start_row = maze->start_row;
	start_col = maze->start_col;


	// init a map with the same dimensions as the charmap.
	int **intMaze = malloc(height * sizeof(int*));
	assert(intMaze);
	for(heightIndex = 0; heightIndex < height; heightIndex++)
	{
		intMaze[heightIndex] = malloc(width * sizeof(int));
		assert(intMaze[heightIndex]);
	}

	// set all values in the intMap to 
	for(heightIndex = 0; heightIndex < height; heightIndex++)
	{
		for(widthIndex = 0; widthIndex < width; widthIndex++)
		{
			intMaze[heightIndex][widthIndex] = -1;
		}
	}

	// start position is set to 0
	intMaze[start_row][start_col] = 0;
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
					if(intMaze[heightIndex][widthIndex+1] == -1 && 
						(maze->map[heightIndex][widthIndex+1] == ' ' || 
							maze->map[heightIndex][widthIndex+1] == 'E'))
					{
						intMaze[heightIndex][widthIndex+1] = currentNumber + 1;
					}
					// fill south with the currentNumber + 1 if possible.
					if(intMaze[heightIndex+1][widthIndex] == -1 && 
						(maze->map[heightIndex+1][widthIndex] == ' ' || 
							maze->map[heightIndex+1][widthIndex] == 'E'))
					{
						intMaze[heightIndex+1][widthIndex] = currentNumber + 1;
					}
					// fill west with the currentNumber + 1 if possible.
					if(intMaze[heightIndex][widthIndex-1] == -1 && 
						(maze->map[heightIndex][widthIndex-1] == ' ' || 
							maze->map[heightIndex][widthIndex-1] == 'E'))
					{
						intMaze[heightIndex][widthIndex-1] = currentNumber + 1;
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
	
	int currentRow = maze->exit_row;
	int currentCol = maze->exit_col;

	// fill the map from back to front with dots
	for(int index = currentNumber - 1; index > 0; index--)
	{
		// if the position NORTH of the current position is the number
		// current position - 1 (or index) the move of routeIndex = SOUTH
		if(intMaze[currentRow-1][currentCol] == index)
		{
			currentRow -= 1;
		}

		// if the position EAST of the current position is the number
		// current position - 1 (or index) the move of routeIndex = WEST
		else if(intMaze[currentRow][currentCol+1] == index)
		{
			currentCol += 1;
		}

		// if the position SOUTH of the current position is the number
		// current position - 1 (or index) the move of routeIndex = NORTH
		else if(intMaze[currentRow+1][currentCol] == index)
		{
			currentRow += 1;
		}

		// if the position WEST of the current position is the number
		// current position - 1 (or index) the move of routeIndex = EAST
		else if(intMaze[currentRow][currentCol-1] == index)
		{
			currentCol -= 1;
		}
		maze->map[currentRow][currentCol] = '.';
	}
	// exit was found.
	return currentNumber;
}