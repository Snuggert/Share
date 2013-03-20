#include <stdio.h>

#include "maze.c"

int main (int argc, char **argv) {
    maze_t *maze;

    /* check args */
    if (argc != 2) {
        printf("usage: %s <maze file>\n", argv[0]);
        return 2;
    }

    /* Read maze */
    maze = read_maze(argv[1]);

    /* Print maze, without marker */
    print_maze(maze, -1, -1);


    cleanup_maze(maze);
    return 0;
}
