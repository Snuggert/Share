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

	storage1 = maakLoods();
	storage2 = maakLoods();
	printf("\nWelkom bij ons theebedrijf. Geef opdrachten:\n\n");
	while(1)
	{
		line = getOperation(line);
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
		else if(!strcmp(token, "stop"))
		{
			break;
		}
		else
		{
			printf("Commando niet herkent...\n");
			printf("Voor lijst met commando's typ help.\n");
		}
		free(line);
	}
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
	printf("opslaan$ @ ($ is het container getal.) ");
	printf("(@ is wat er opgeslagen moet worden.)'\n");
	printf("leveren$ ($ is het container getal.)\n");
	printf("verplaatsen$@ ($ is de oorsprongs container) ");
	printf("(@ is de bestemmings container");
	printf("stop\n");
}