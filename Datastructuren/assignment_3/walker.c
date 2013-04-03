/*
 * File: walker.c
 * 
 * This file contains functions that are used by a walker that walks through 
 * a maze.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 23-02-2013
 */

#include "walker.h"
#include "maze.h"

/* Incomplete definitions of the walker support function . */
int checkMove(int direction, struct maze_t* maze, struct walker_t* walker)
{
	char *charMap = maze->map;
	if(direction == NORTH)
	{
		if(charMap[(walker->yPos - 1) * maze->width + walker->xPos] == ' ' ||
			charMap[(walker->yPos - 1) * maze->width + walker->xPos] == 'E' ||
			charMap[(walker->yPos - 1) * maze->width + walker->xPos] == 'S')
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(direction == EAST)
	{
		if(charMap[walker->yPos * maze->width + walker->xPos + 1] == ' ' ||
			charMap[walker->yPos * maze->width + walker->xPos + 1] == 'E' ||
			charMap[walker->yPos * maze->width + walker->xPos + 1] == 'S')
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(direction == SOUTH)
	{
		if(charMap[(walker->yPos + 1) * maze->width + walker->xPos] == ' ' ||
			charMap[(walker->yPos + 1) * maze->width + walker->xPos] == 'E' ||
			charMap[(walker->yPos + 1) * maze->width + walker->xPos] == 'S')
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(direction == WEST)
	{
		if(charMap[walker->yPos * maze->width + walker->xPos - 1] == ' ' || 
			charMap[walker->yPos * maze->width + walker->xPos - 1] == 'E' ||
			charMap[walker->yPos * maze->width + walker->xPos - 1] == 'S')
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 2;
	}
}

int atExit(struct maze_t* maze, struct walker_t* walker)
{
	if(walker->xPos == maze->endX && walker->yPos == maze->endY)
	{
		return 1;
	}
	else
	{
		return 0;
	}    
}

struct walker_t* initWalker(struct maze_t* maze)
{
	struct walker_t *walker;
	walker = malloc( sizeof(struct walker_t) );
	walker->xPos = maze->startX;
	walker->yPos = maze->startY;
	return walker;
}

int moveWalker(int direction, struct walker_t* walker, struct maze_t* maze)
{
	if(direction == NORTH)
	{
		// if move is valid move the walker.
		if(checkMove(direction, maze, walker))
		{
			walker->yPos -= 1;
			return 1;
		}
		else
		{
			return 0;
		}
	}

	else if(direction == EAST)
	{
		// if move is valid move the walker.
		if(checkMove(direction, maze, walker))
		{
			walker->xPos += 1;
			return 1;
		}
		else
		{
			return 0;
		}
	}

	else if(direction == SOUTH)
	{
		// if move is valid move the walker.
		if(checkMove(direction, maze, walker))
		{
			walker->yPos += 1;
			return 1;
		}
		else
		{
			return 0;
		}
	}

	else if(direction == WEST)
	{
		// if move is valid move the walker.
		if(checkMove(direction, maze, walker))
		{
			walker->xPos -= 1;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

void cleanupWalker(struct walker_t* walker)
{
	free(walker);
}