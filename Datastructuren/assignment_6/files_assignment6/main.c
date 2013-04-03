#include <stdio.h>

#include "maze.c"
#include "solver.c"

int main (int argc, char **argv) {
    int steps;
    maze_t *maze;

    /* check args */
    if (argc != 2) {
        printf("usage: %s <maze file>\n", argv[0]);
        return 2;
    }

    /* Read maze */
    maze = read_maze(argv[1]);
    steps = breadthFirst(maze);
    /* Print maze, without marker */
    if(steps == 0)
    {
        printf("No exit was found.\n");
    }
    else
    {
        printf("\nThe number of steps required is: %d\n", steps);
    }
    
    print_maze(maze, -1, -1);

    cleanup_maze(maze);
    return 0;
}
