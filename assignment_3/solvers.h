#ifndef SOLVERS_H
#define SOLVERS_H

int mySuperMazeSolverFunction(struct maze_t* maze, int **route);
 // solver functions that will return a direction for the next step. 
void randomDirection(struct maze_t* maze, struct walker_t* walker);
int followWall(struct maze_t* maze, struct walker_t* walker, int direction);

#endif
