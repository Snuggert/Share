/*
 * File: main.c
 * 
 * This file contains a program in c to solve a maze with different algorithms
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 23-02-2013
 */

#include "maze.c"
#include "walker.c"
#include "solvers.c"
#include "main.h"

#include "time.h"

int main (int argc, char **argv) {
    // check if argument is given.
    if(argc != 2)
    {
        perror("No mazefile given to program.");
        exit(EXIT_FAILURE);
    }
    struct maze_t* maze;
    struct walker_t* walker;
    int count, direction, *route, routelength, choice;
    char *fileName;

    fileName = argv[1];
    // read the maze into the maze struct.
    maze = readMaze(fileName);
    // initialize the walker on the startposition in the maze
    walker = initWalker(maze);
    printf("Maze file loaded.\n");

    // Let user pick decryption method.
    choice=getDecryptionFromUser(1,3);

    clock_t timespent;
    // start the clock for the algorithm
    timespent=clock();

    // all results are put into the result.txt file
    FILE *filePointer;
    filePointer=fopen("result.txt", "w");
    fprintf(filePointer, "This file contains the results with");
    fprintf(filePointer, " decryption method: %d\n", choice);
    fclose(filePointer);

    // random method
    if(choice == 1)
    {
        count = 0;
        // Go to random direction until exit is found or MAX_STEPS is reached.
        while (count < MAX_STEPS) {
            count++;
            randomDirection(maze, walker);
            printMaze(maze, walker, count);
            if(atExit(maze, walker))
            {
                printf("\nExit found after %d steps\n", count);
                break;
            }       
        }
        // If count is indeed MAX_STEPS no exit is found and a error is returned
        if(count == MAX_STEPS)
        {
            perror("Exit not found after MAX_STEPS steps");
            exit(EXIT_FAILURE);
        }
    }

    // wall following method
    else if(choice == 2)
    {
        count = 0;
        direction = 0;
        // Follow the walls until exit is found or max steps is reached.
        while (count < MAX_STEPS) {
            count++;
            direction = followWall(maze, walker, direction);
            printMaze(maze, walker, count);
            if(atExit(maze, walker))
            {
                printf("\nExit found after %d steps\n", count);
                break;
            }       
        }
        // If count is indeed MAX_STEPS no exit is found and a error is returned
        if(count == MAX_STEPS)
        {
            perror("Exit not found after MAX_STEPS steps");
            exit(EXIT_FAILURE);
        }
    }

    // My own method.
    else if(choice == 3)
    {
        // solve the maze and get the steps in the route array.
        routelength = mySuperMazeSolverFunction(maze, &route);
        // if routelength == 0 no exit is found by the algorithm.
        if(routelength == 0)
        {
            perror("Exit not found by Algorithm.");
            exit(EXIT_FAILURE);
        }
        int index = 0;
        // While exit is not found let walker make steps.
        while(1)
        {
            if(!moveWalker(route[index], walker, maze))
            {
                perror("Algorithm provided wrong move.");
                exit(EXIT_FAILURE);
            }
            index++;
            printMaze(maze, walker, index);
            if(atExit(maze, walker))
            {
                printf("\nExit found after %d steps\n", index);
                break;
            }
        }
    }
   
    timespent = clock() - timespent;
    // return time spent to user.
    printf("Time spent is: %f seconds \n", ((float)timespent)/CLOCKS_PER_SEC);
    // return to user where results can be found after completion algorithm.
    printf("Results can be found in result.txt");
    cleanupMaze(maze);
    cleanupWalker(walker);
    return 0;
}

// get decryption type from user.
int getDecryptionFromUser(int min, int max)
{
   printf("\nDecryption options:\n");
   printf("Random [1]\nWall Follower [2]\nCustom Follower[3]\n");
   printf("\nWaiting for choice: ");
   int input;   
   input = 0;

   while (scanf("%d",&input) != 1 || input < min || input > max)
   {
      printf("Wrong input: ");
   }
   return input;
}