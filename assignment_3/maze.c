#include "maze.h"

/* Incomplete definitions of the maze support function . */
maze_t *init_maze(int width, int height)
{
	maze_t *maze;
	maze->width = width;
	maze->height = height;
	maze->map = malloc((width * height + 1) * sizeof(char))
	return maze;
}

maze_t *read_maze(char *fileName)
{
	int width, height;
	long size;
	char ch, *tempMaze, *token;
	char *search;
	maze_t *maze;
	FILE *filePointer = fopen(fileName,"r");

	if (filePointer == NULL)
	{
		perror("Error reading file");
		exit(EXIT_FAILURE);
	}

	fseek(filePointer, 0, SEEK_END);
	size = sizeof(char) * ftell(*filePointer);
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

	for(int heightIndex = 0; heightIndex < height; height++)
	{
		token = strtok(NULL, search);
		if(token == NULL)
		{
			printf("Error in textfile.\n");
			exit(EXIT_FAILURE);
		}

		for(int widthIndex = 0; widthIndex < width; width++)
		{
			maze->map[width * heightIndex + widthIndex] = token[widthIndex];
			if(token[widthIndex] == 'S')
			{

				maze->startX = widthIndex;
				maze->startY = heightIndex;
			}
		}
	}


    maze = init_maze(width, height);
	if()
	{

	}
    maze.map = malloc(10*10);
	return maze;
}

void print_maze(maze_t maze)
{

}

void cleanup_maze ()
{

}
