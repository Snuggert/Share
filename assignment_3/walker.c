#include "walker.h"

/* Incomplete definitions of the walker support function . */
int check_move()
{
    return 0;
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

struct walker_t* init_walker(struct maze_t* maze)
{
	struct walker_t *walker;
	walker = malloc( sizeof(struct walker_t) );
	walker->xPos = maze->startX;
	walker->yPos = maze->startY;
	return walker;
}

int move_walker()
{
	return 0;
}

void cleanup_walker()
{
}