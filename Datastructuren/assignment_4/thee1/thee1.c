/*
 * File: thee1.c
 * 
 * This program is a managing program for a tea company.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 23-02-2013
 */

#include "stdio.h" 
#include "string.h"

#include "loods1.h"
#include "loods1.c"
#include "thee1.h"

int main (int argc, char **argv)
{
	struct loods1 *storage;
	char *line, *token, *search, *leverenResult;
	line = malloc( 50 * sizeof(char) );

	storage = maakLoods();
	printf("\nWelkom bij ons theebedrijf. Geef opdrachten:\n\n");
	// Start console.
	while(1)
	{
		line = getOperation(line);
		search = " ";
		token = strtok(line, search);

		// If token is null no searchresults are found and the command is not
		// recognized.
		if(token == NULL)
		{
			printf("Commando niet herkent...\n");
			printf("Voor lijst met commando's typ help.\n");
		}

		// If token is help print a list of commands.
		else if(!strcmp(token, "help"))
		{
			printCommands();
		}

		// If token is leveren deliver the tea from the storage.
		else if(!strcmp(token, "leveren"))
		{
			leverenResult = leveren(storage);
			// After leveren result is retrieved check if it is not NULL print 
			// the result, else there is no more tea in stock.
			if(leverenResult != NULL)
			{
				printf("%s wordt geleverd.\n", leverenResult);
			}
			else
			{
				printf("Er is geen thee meer in voorraad.\n");
			}
			free(leverenResult);
		}

		// If token is opslaan store tea in the storage.
		else if(!strcmp(token, "opslaan"))
		{
			// Search for the end of line for what to store.
			search = "\n";
			token = strtok(NULL, search);
			// if nothing is found return to user to give something to store.
			if(token == NULL)
			{
				printf("Niks om op te slaan meegegeven.\n");
			}
			// else store the content.
			else
			{
				opslaan(storage, token);
				printf("%s wordt opgeslagen.\n", token);
			}	
		}

		// break the loop when the stop command is given.
		else if(!strcmp(token, "stop"))
		{
			break;
		}

		// Else the command is not recognized.
		else
		{
			printf("Commando niet herkent...\n");
			printf("Voor lijst met commando's typ help.\n");
		}
		free(line);
	}

	// after the loop free the memory.
	sloopLoods(storage);
	return 0;
}

// Get operation from user.
char* getOperation(char *line)
{
	char *p;
	line = malloc(50 * sizeof(char));
	printf("> ");
	if (fgets(line, 50, stdin) != NULL)
	{
		// Switch the newline with a NULL terminator.
		if ((p = strchr(line, '\n')) != NULL)
		{
			*p = '\0';
		}
	}
	return line;
}

// Print the possible commands.
void printCommands()
{
	printf("Commands:\n");
	printf("opslaan 'wat er opgeslagen moet worden.'\n");
	printf("leveren\n");
	printf("stop\n");
}