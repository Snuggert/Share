/*
 * File: thee3.c
 * 
 * This program is a managing program for a tea company.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 23-02-2013
 */

#include "stdio.h" 
#include "string.h"

#include "loods3.h"
#include "loods3.c"
#include "thee3.h"

int main (int argc, char **argv)
{
	struct loods3 *storage1, *storage2;
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

		// If token is leveren deliver the tea from storage 2.
		else if(!strcmp(token, "leveren"))
		{
			// If storage2 is empty and storage1 is not, switch through the tea.
			if(leeg(storage2) && !leeg(storage1))
			{
				while(1)
				{
					leverenResult = leveren(storage1);
					if(leverenResult != NULL)
					{
						printf("%s wordt verplaatst van loods 1 naar loods 2.\n", leverenResult);
						opslaan(storage2, leverenResult);
					}
					else
					{
						break;
					}
				}	
			}
			leverenResult = leveren(storage2);
			if(leverenResult != NULL)
			{
				printf("%s wordt geleverd uit loods 2.\n", leverenResult);
			}
			else
			{
				printf("Er is geen thee meer in voorraad.\n");
			}		
		}

		// If token is opslaan store tea in the storage1.
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
				opslaan(storage1, token);
				printf("%s wordt opgeslagen in loods 1.\n", token);
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
	free(line);
	sloopLoods(storage1);
	sloopLoods(storage2);
	return 0;
}

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

void printCommands()
{
	printf("Commands:\n");
	printf("opslaan @");
	printf("(@ is wat er opgeslagen moet worden.)'\n");
	printf("leveren\n");
	printf("stop\n");
}