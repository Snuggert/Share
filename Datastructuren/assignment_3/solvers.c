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
#include "walker.h"
#include "solvers.h"

/* Will contain the definitions of the maze solver functions. */
int mySuperMazeSolverFunction(struct maze_t *maze, int **route) 
{
	int *intMaze, size, currentNumber, currentPosition, width, height;
	width = maze->width;
	height = maze->height;
	char *charMap = maze->map;
	size = height * width;
	intMaze = malloc(size * sizeof(int));
	for(int index = 0; index < size; index++)
	{
		intMaze[index] = -1;
	}
	intMaze[maze->startY * width + maze->startX] = 0;
	currentNumber = 0;

	while(currentNumber < size)
	{	
		// if currentnumber is located at the exit of the maze break the filling.
		if(intMaze[maze->endY * width + maze->endX] == currentNumber)
		{
			break;
		}
		for(int index = 0; index < size; index++)
		{
			if(intMaze[index] == currentNumber)
			{
				// fill north with the currentNumber + 1 if possible.
				if(intMaze[index-width] == -1 && 
					(charMap[index-width] == ' ' || charMap[index-width] == 'E'))
				{
					intMaze[index-width] = currentNumber + 1;
				}
				// fill east with the currentNumber + 1 if possible.
				if(intMaze[index+1] == -1 && 
					(charMap[index+1] == ' ' || charMap[index+1] == 'E'))
				{
					intMaze[index+1] = currentNumber + 1;
				}
				// fill south with the currentNumber + 1 if possible.
				if(intMaze[index+width] == -1 && 
					(charMap[index+width] == ' ' || charMap[index+width] == 'E'))
				{
					intMaze[index+width] = currentNumber + 1;
				}
				// fill west with the currentNumber + 1 if possible.
				if(intMaze[index-1] == -1 && 
					(charMap[index-1] == ' ' || charMap[index-1] == 'E'))
				{
					intMaze[index-1] = currentNumber + 1;
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

// generate a random direction based on time.
void randomDirection(struct maze_t* maze, struct walker_t* walker)
{
	// possible directions are null to three.
	while(!moveWalker(rand() % 4, walker, maze));
}

// Follow the left wall.
int followWall(struct maze_t* maze, struct walker_t* walker, int direction)
{
		// Rotate direction to the right.
		direction--;
		if(direction < 0)
		{
			direction += 4;
		}
		// While there is a wall turn to the right.
		while (!moveWalker(direction, walker, maze)) 
		{
			direction = (direction + 1) % 4;
		}

		return direction;
}