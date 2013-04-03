#ifndef WALKER_H
#define WALKER_H

// Complete type declarations. 
struct walker_t
{
    int xPos, yPos;
};

struct maze_t;

// Complete declarations of the support functions. 
struct walker_t* initWalker(struct maze_t* maze);
int moveWalker(int direction, struct walker_t* walker, struct maze_t* maze);
int atExit(struct maze_t* maze, struct walker_t* walker);
int checkMove(int direction, struct maze_t* maze, struct walker_t* walker);
void cleanupWalker(struct walker_t* walker);

#endif
