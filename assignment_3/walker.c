#include "walker.h"
#include "maze.h"

/* Incomplete definitions of the walker support function . */
int check_move(int direction, struct maze_t* maze, struct walker_t* walker)
{
	char *charMap = maze->map;
	if(direction == NORTH)
	{
		if(charMap[(walker->yPos - 1) * maze->width + walker->xPos] == ' ' ||
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

int at_exit(struct maze_t* maze, struct walker_t* walker)
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

struct walker_t* move_walker(int direction, struct walker_t* walker, struct maze_t* maze)
{
	if(direction == NORTH)
	{
		// if move is valid move the walker.
		if(check_move(direction, maze, walker))
		{
			walker->yPos -= 1;
		}
	}

	else if(direction == EAST)
	{
		// if move is valid move the walker.
		if(check_move(direction, maze, walker))
		{
			walker->xPos += 1;
		}
	}

	else if(direction == SOUTH)
	{
		// if move is valid move the walker.
		if(check_move(direction, maze, walker))
		{
			walker->yPos += 1;
		}
	}

	else if(direction == WEST)
	{
		// if move is valid move the walker.
		if(check_move(direction, maze, walker))
		{
			walker->xPos -= 1;
		}
	}
	return walker;
}

void cleanup_walker()
{
}