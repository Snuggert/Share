/*
 * File: maze.c
 * 
 * This file contains the functions used by a maze struct.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 23-02-2013
 */

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "maze.h"
#include "walker.h"

// initialize the struct with the size of the given array.
struct maze_t *initMaze(int width, int height)
{
	struct maze_t *maze;
	maze = malloc( sizeof(struct maze_t) );
	maze->width = width;
	maze->height = height;
	maze->map = malloc( (width * height + 1) * sizeof(char) );

	// set all positions to zero.
	maze->startX = 0;
	maze->startY = 0;
	maze->endX = 0;
	maze->endY = 0;
	return maze;
}

// read the maze file into a struct.
struct maze_t *readMaze(char* fileName)
{
	int width, height;
	long size;
	char *tempMaze, *token;
	char *search;
	struct maze_t *maze;
	FILE *filePointer = fopen(fileName,"r");

	if (filePointer == NULL)
	{
		perror("Error reading file");
		exit(EXIT_FAILURE);
	}

	fseek(filePointer, 0, SEEK_END);
	size = sizeof(char) * ftell(filePointer);
	rewind(filePointer);
	tempMaze = malloc(size);

	// Read file into char array.
	fread(tempMaze, sizeof(char), size, filePointer);

	search = ",";
	token = strtok(tempMaze, search);
	if(token != NULL)
	{
		height = strtol(token, NULL, 10);
	}
	else
	{
		free(tempMaze);
		perror("No height found.");
		exit(EXIT_FAILURE);
	}

	search = "\n";
	token = strtok(NULL, search);
	if(token != NULL)
	{
		width = strtol(token, NULL, 10);
	}
	else
	{
		free(tempMaze);
		perror("No width found.");
		exit(EXIT_FAILURE);
	}

	maze = initMaze(width, height);

	for(int heightIndex = 0; heightIndex < height; heightIndex++)
	{
		token = strtok(NULL, search);
		if(token == NULL)
		{
			free(tempMaze);
			cleanupMaze(maze);
			perror("Error in textfile.");
			exit(EXIT_FAILURE);
		}

		for(int widthIndex = 0; widthIndex < width; widthIndex++)
		{
			maze->map[width * heightIndex + widthIndex] = token[widthIndex];
			if(token[widthIndex] == 'S')
			{
				maze->startX = widthIndex;
				maze->startY = heightIndex;
			}
			if(token[widthIndex] == 'E')
			{
				maze->endX = widthIndex;
				maze->endY = heightIndex;
			}
			if((widthIndex == 0 || widthIndex == width -1) && token[widthIndex] != '#')
			{
				free(tempMaze);
				cleanupMaze(maze);
				perror("Holes in maze walls.");
				exit(EXIT_FAILURE);
			}
		}
	}

	if(maze->endX == 0 || maze->endY == 0)
	{
		free(tempMaze);
		cleanupMaze(maze);
		perror("No exit found in file.");
		exit(EXIT_FAILURE);
	}
	if(maze->endX == 0 || maze->endY == 0)
	{
		free(tempMaze);
		cleanupMaze(maze);
		perror("No start found in file.");
		exit(EXIT_FAILURE);
	}

	free(tempMaze);
	return maze;
}

// print the maze with the walker position marked by an X.
void printMaze(struct maze_t* maze, struct walker_t* walker, int count)
{
	char *mapArray;
	int size, index, posInArray;
	size = maze->width * maze->height;
	mapArray = malloc(size * sizeof(char) );

	// copy the map from the maze to a new mapArray.
	for(index = 0; index < size; index++)
	{
		mapArray[index] = maze->map[index];
	}

	posInArray = walker->yPos * maze->width + walker->xPos;
	mapArray[posInArray] = 'X';
	long numberOfChars = maze->height * maze->width;

    printf("step: %d\n", count);
	for(index = 0; index < numberOfChars; index++)
	{
		printf("%c", mapArray[index]);
		if(index % maze->width == maze->width - 1)
		{
			printf("\n");
		}
	}

	free(mapArray);
}

// free up memory.
void cleanupMaze(struct maze_t* maze)
{
	free(maze->map);
	free(maze);
}