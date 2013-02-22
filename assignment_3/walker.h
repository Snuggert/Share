#ifndef WALKER_H
#define WALKER_H

/* Incomplete type declaration. */
struct walker_t
{
    int xPos, yPos;
};

struct maze_t;

/* Incomplete declarations of the support functions. */
struct walker_t* initWalker(struct maze_t* maze);
int move_walker();
int at_exit(struct maze_t* maze, struct walker_t* walker);
int check_move();
void cleanup_walker();

#endif
