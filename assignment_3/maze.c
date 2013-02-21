#include "maze.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

/* Incomplete definitions of the maze support function . */
maze_t *initMaze(int width, int height)
{
	maze_t *maze;
	maze = malloc( sizeof(maze_t) );
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

maze_t *readMaze(char* fileName)
{
	int width, height;
	long size;
	char *tempMaze, *token;
	char *search;
	maze_t *maze;
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
	search = "\n";
	token = strtok(NULL, search);
	if(token != NULL)
	{
		width = strtol(token, NULL, 10);
	}

	maze = initMaze(width, height);

	for(int heightIndex = 0; heightIndex < height; heightIndex++)
	{
		token = strtok(NULL, search);
		if(token == NULL)
		{
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
				perror("Holes in maze walls.");
				exit(EXIT_FAILURE);
			}
		}
	}

	if(maze->endX == 0 || maze->endY == 0)
	{
		perror("No exit found in file.");
		exit(EXIT_FAILURE);
	}
	if(maze->endX == 0 || maze->endY == 0)
	{
		perror("No start found in file.");
		exit(EXIT_FAILURE);
	}

	free(tempMaze);
	return maze;
}

void printMaze(maze_t* maze)
{
	char *mapArray = maze->map;
	long numberOfChars = maze->height * maze->width;
	for(int index = 0; index < numberOfChars; index++)
	{
		printf("%c", mapArray[index]);
		if(index % maze->width == maze->width - 1)
		{
			printf("\n");
		}
	}
}

void cleanupMaze()
{

}
