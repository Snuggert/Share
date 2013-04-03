#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ARGS        (1024)
#define MAX_LINE        (2 * MAX_ARGS)

void scan_line();
void do_exit ();
void do_cd(char* dir);

int main( int argc, char *argv[] )
{
	while(1)
	{
		scanline();
	}
}

void scan_line()
{
	char *cmd, *delims, *token, *cwd;

	cmd = malloc(sizeof(char)*MAX_LINE);
	cwd = malloc(sizeof(char)*1024);

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
  		fprintf(stdout, "%s>", cwd);
	}
  	else
  	{
		perror("getcwd() error");
  	}

	if ( fgets(cmd, MAX_LINE, stdin) != NULL )
	{
		char *newline = strchr(cmd, '\n'); /* search for newline character */
		if ( newline != NULL )
		{
			*newline = '\0'; /* overwrite trailing newline */
		}
	}
	delims = " ";
	// Compare first part of read string, with the string cd, 
	// if it matches send rest of string to do_cd
	token = strtok(cmd,delims);
	if(strcmp(token, "cd") == 0)
	{
		delims = "";
		do_cd(strtok(NULL, delims));
	}

	else if(strcmp(text, "exit") == 0)
	{
		do_exit();
	}

	else
	{
		parse_command(cmd);
	}
}

void do_exit()
{
	exit(0);
}

void do_cd(char* dir)
{
	if(chdir(dir) != 0)
	{
		printf("%s :No such file or directory.\n", dir);
	}
}