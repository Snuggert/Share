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
	while(1)
	{
		getOperation(line);
		search = " ";
		token = strtok(line, search);
		if(token == NULL)
		{
			printf("Commando niet herkent...\n");
			printf("Voor lijst met commando's typ help.\n");
		}
		else if(!strcmp(token, "help"))
		{
			printCommands();
		}
		else if(!strcmp(token, "leveren"))
		{
			leverenResult = leveren(storage);
			if(leverenResult != NULL)
			{
				printf("%s wordt geleverd.\n", leverenResult);
			}
			else
			{
				printf("Er is geen thee meer in voorraad.\n");
			}	
		}
		else if(!strcmp(token, "opslaan"))
		{
			search = "\n";
			token = strtok(NULL, search);
			if(token == NULL)
			{
				printf("Niks om op te slaan meegegeven.\n");
			}
			else
			{
				opslaan(storage, token);
				printf("%s wordt opgeslagen.\n", token);
			}	
		}
		else if(!strcmp(token, "exit"))
		{
			sloopLoods(storage);
			break;
		}
		else
		{
			printf("Commando niet herkent...\n");
			printf("Voor lijst met commando's typ help.\n");
		}
	}
	return 0;
}

void getOperation(char *line)
{
	char *p;
	printf("> ");
	if (fgets(line, 50, stdin) != NULL)
	{
		// Switch the newline with a NULL terminator.
		if ((p = strchr(line, '\n')) != NULL)
		{
			*p = '\0';
		}
	}
}

void printCommands()
{
	printf("Commands:\n");
	printf("opslaan 'wat er opgeslagen moet worden.'\n");
	printf("leveren\n");
	printf("exit\n");
}