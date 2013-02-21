#include "maze.c"
#include "walker.c"
#include "solvers.c"
#include "main.h"

int main (int argc, char **argv) {
    // check if argument is given.
    if(argc != 2)
    {
        perror("No mazefile given to program.");
        exit(EXIT_FAILURE);
    }
    struct maze_t* maze;
    struct walker_t* walker;
    int count, dir;
    char *fileName;

    fileName = argv[1];

    maze = readMaze(fileName);
    printMaze(maze);

    // count = 0;
    // while (count < MAX_STEPS) {
    //     count++;
    //     dir = my_super_maze_solver_function(maze, walker);
    //     move_walker(maze, walker, dir);
    //     print_maze(maze, walker->row, walker->col);
    //     printf("%d\n", count);
    //     if (at_exit(maze, walker))
    //         break;
    // }

    // if (count < MAX_STEPS)
    // {
    //     printf("Found exit after %d steps\n", count);
    // }


    return 0;
}
