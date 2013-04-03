/*
 * File: thee2.c
 * 
 * This program is a managing program for a tea company.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 23-02-2013
 */

#include "stdio.h" 
#include "string.h"

#include "loods2.h"
#include "loods2.c"
#include "thee2.h"

int main (int argc, char **argv)
{
	struct loods2 *storage1, *storage2;
	char *line, *token, *search, *leverenResult;

	// Init storages.
	storage1 = maakLoods();
	storage2 = maakLoods();
	printf("\nWelkom bij ons theebedrijf. Geef opdrachten:\n\n");
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

		// If token is leveren deliver the tea from storage 1 or 2.
		else if(!strcmp(token, "leveren1") || !strcmp(token, "leveren2"))
		{
			if(token[7] == '1')
			{
				leverenResult = leveren(storage1);
				if(leverenResult != NULL)
				{
					printf("%s wordt geleverd uit loods 1.\n", leverenResult);
				}
				else
				{
					printf("Er is geen thee meer in voorraad.\n");
				}
				free(leverenResult);
			}
			else if(token[7] == '2')
			{
				leverenResult = leveren(storage2);
				if(leverenResult != NULL)
				{
					printf("%s wordt geleverd uit loods 2.\n", leverenResult);
				}
				else
				{
					printf("Er is geen thee meer in voorraad.\n");
				}
				free(leverenResult);
			}
			else
			{
				printf("Loods bestaat niet\n");
			}
		}

		// If token is opslaan store tea in the storage.
		else if(!strcmp(token, "opslaan1") || !strcmp(token, "opslaan2"))
		{
			search = "\n";
			if(token[7] == '1')
			{
				token = strtok(NULL, search);
				if(token == NULL)
				{
					printf("Niks om op te slaan meegegeven.\n");
				}
				else
				{
					opslaan(storage1, token);
					printf("%s wordt opgeslagen in loods 1.\n", token);
				}	
			}

			else if(token[7] == '2')
			{
				token = strtok(NULL, search);
				if(token == NULL)
				{
					printf("Niks om op te slaan meegegeven.\n");
				}
				else
				{
					opslaan(storage2, token);
					printf("%s wordt opgeslagen in loods 2.\n", token);
				}
			}
			else
			{
				printf("Loods bestaat niet\n");
			}	
		}

		// The verplaatsen command moves a string from one struct to another.
		else if(!strcmp(token, "verplaatsen12") 
			|| !strcmp(token, "verplaatsen21"))
		{
			if(token[11] == '1')
			{
				leverenResult = leveren(storage1);
				if(leverenResult != NULL)
				{
					printf("%s wordt verplaatst van loods 1 naar loods 2.\n", leverenResult);
					opslaan(storage2, leverenResult);
				}
				else
				{
					printf("Er is geen thee meer in voorraad in loods 1.\n");
				}	
			}

			else if(token[11] == '2')
			{
				leverenResult = leveren(storage2);
				if(leverenResult != NULL)
				{
					printf("%s wordt verplaatst van loods 2 naar loods 1.\n", leverenResult);
					opslaan(storage1, leverenResult);
				}
				else
				{
					printf("Er is geen thee meer in voorraad in loods 2.\n");
				}	
			}
			else
			{
				printf("Loods bestaat niet\n");
			}
			free(token);
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
	free(line);
	sloopLoods(storage1);
	sloopLoods(storage2);
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
	printf("opslaan$ @ ($ is het container getal.) ");
	printf("(@ is wat er opgeslagen moet worden.)'\n");
	printf("leveren$ ($ is het container getal.)\n");
	printf("verplaatsen$@ ($ is de oorsprongs container) ");
	printf("(@ is de bestemmings container");
	printf("stop\n");
}