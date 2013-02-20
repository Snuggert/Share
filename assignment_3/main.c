#include "main.h"
#include "maze.c"
#include "walker.c"
#include "solvers.c"

#define MAX_STEPS 10000

int main (int argc, char **argv) {
    maze_t* maze;
    walker_t* walker;
    int count, dir;

    /* check your args, read maze here, init walker.. */
    /* ... */

    count = 0;
    while (count < MAX_STEPS) {
        count++;
        dir = my_super_maze_solver_function(maze, walker);
        move_walker(maze, walker, dir);
        print_maze(maze, walker->row, walker->col);
        printf("%d\n", count);
        if (at_exit(maze, walker))
            break;
    }

    if (count < MAX_STEPS)
    {
        printf("Found exit after %d steps\n", count);
    }


    return 0;
}
