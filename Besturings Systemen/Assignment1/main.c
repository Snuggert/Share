#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ARGS        (1024)
#define MAX_LINE        (2 * MAX_ARGS)

void scanline();
void do_exit ();
void do_cd(char* dir);

int main( int argc, char *argv[] )
{
	scanline();
}

void scanline()
{
	char *text, *delim;
	text = malloc(sizeof(char)*MAX_LINE);

	printf(">");
	if ( fgets(text, MAX_LINE, stdin) != NULL )
	{
		char *newline = strchr(text, '\n'); /* search for newline character */
		if ( newline != NULL )
		{
			*newline = '\0'; /* overwrite trailing newline */
		}
	}

	// Compare first part of read string, with the string cd, 
	// if it matches send rest of string to do_cd
	delim = ' ';
	if(strcmp(strtok(text,delim),'cd'))
	{
		delim = '\0';
		do_cd(strtok(NULL,'\0'));
	}

	else if(strcmp(text,'exit') == 0)
	{
		do_exit();
	}

}

void do_exit()
{
	exit(0);
}

void do_cd(char* dir)
{
	printf("%s\n", dir);
}