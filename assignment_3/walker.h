#ifndef WALKER_H
#define WALKER_H

/* Incomplete type declaration. */
typedef struct {
    int xPos, yPos;
} walker_t;


/* Incomplete declarations of the support functions. */
walker_t* init_walker(maze_t* maze);
int move_walker();
int at_exit(maze_t* maze, walker_t* walker);
int check_move();
void cleanup_walker();

#endif
