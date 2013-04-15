/*
 * File: main.c
 * 
 * This file contains a very simple shell implementation, 
 * this shell includes a form of piping.
 *
 * Author: Abe Wiersma (Snuggert)
 * Date: 15-04-2013
 */


// Define XOPEN_SOURCE, this was necessary for my version of linux, this took me 
// some time to figure out but my version of linux has some kind of a weird 
// version of signal.h
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
// #include <limits.h>

#define PATH_MAX        4096    /* # chars in a path name including nul */
#define STDIN 0
#define STDOUT 1

struct sigaction action;

void signal_callback_handler(int signum);
void scan_line();
void do_exit();
void do_cd(char* dir);
void do_read_from_file(char *cmd);
void parse_command(char ***commands, int number_of_commands, char *cmd);
int countcommands(char *cmd);
void fork_pipes(int number_of_args, char ***cmds);
int spawn_proc(int in, int out, char **cmd);
void handler(int sig_no);

int main( int argc, char *argv[] )
{

	action.sa_handler = handler;
	sigfillset(&action.sa_mask);
	action.sa_flags = 0;

	/* Redirect sigaction to escape keyboard interups. */
	sigaction(SIGINT, &action, NULL);

	while(1)
	{
		scan_line();
	}
}

// Scan and parse a command given by fgets.
// this function will redirect to inbuilt functions.
void scan_line()
{
	int number_of_args;
	char *cmd, *cmdcpy, *delims, *token, *cwd, ***exec_commands;

	cmd = malloc(sizeof(char)*1024);
	cwd = malloc(PATH_MAX);

	if (getcwd(cwd, PATH_MAX) != NULL)
	{
  		fprintf(stdout, "\n%s>", cwd);
  		free(cwd);
	}
  	else
  	{
  		free(cwd);
		perror("getcwd() error");
  	}

	if ( fgets(cmd, 1024, stdin) == NULL )
	{
		free(cmd);
		return;
	}

	// replace \n with '\0'
	char *newline = strchr(cmd, '\n');
	if(newline != NULL)
	{
		*newline = '|';
	}

	cmdcpy = malloc(sizeof(char)*1024);
	cmdcpy = strcpy(cmdcpy, cmd);
	
	delims = "";
	token = strtok(cmdcpy,delims);
	// Compare first part of read string "exit"
	if(strcmp(token, "exit|") == 0)
	{
		do_exit();
		free(token);
		free(cmdcpy);
	}
	
	// Compare first part of read string "."
	else if(strcmp(token, ".") == 0)
	{
		do_read_from_file(strtok(NULL, delims));
		free(token);
		free(cmdcpy);
	}

	// Compare first part of read string, with the string cd, 
	// if it matches send rest of string to do_cd
	else if(strcmp(token, "cd") == 0)
	{
		delims = "";
		do_cd(strtok(NULL, delims));
		free(token);
		free(cmdcpy);
	}

	else
	{
		number_of_args = countcommands(cmd);
		exec_commands = malloc(sizeof(char**) * number_of_args);
		parse_command(exec_commands, number_of_args, cmd);
		fork_pipes(number_of_args, exec_commands);
		free(exec_commands);
	}
}

// exit from console.
void do_exit()
{
	wait(0);
	exit(0);
}

// do a cd command.
void do_cd(char* dir)
{
	if(chdir(dir) != 0)
	{
		printf("%s :No such file or directory.\n", dir);
	}
}

// Read commands from a file.
void do_read_from_file(char *file)
{
	int length, number_of_args;
	char *line, *token, ***exec_commands;
	FILE *fp;
	fp = fopen(file, "r");
	if(fp == NULL)
	{
		printf("No file found with name: %s\n", file);
	}

	while (getline(&line, &length, fp) != -1) 
	{
		token = strtok(line, "");
		if(strcmp(token, "exit") == 0)
		{
			do_exit();
			free(token);
		}

		else if(strcmp(token, "cd") == 0)
		{
			do_cd(strtok(NULL, ""));
			free(token);
		}

		else
		{
			number_of_args = countcommands(line);
			exec_commands = malloc(sizeof(char**) * number_of_args);
			parse_command(exec_commands, number_of_args, line);
			fork_pipes(number_of_args, exec_commands);
			free(exec_commands);
		}
	}
}

// Parse a command from a string to a array of char arrays parseble by execvp.
void parse_command(char ***exec_commands, int number_of_args, char *cmd)
{
	int first, index, exec_index;
	char **commands, *token;
	commands = malloc( sizeof(char*) * number_of_args );

	first = 1;
	// First split up the whole command.
	while(1)
	{
		if(first)
		{
			token = strtok(cmd, "|");
			commands[0] = token;
			first = 0;
			index = 1;
		}
		else
		{
			token = strtok(NULL, "|");
			if(token != NULL)
			{
				commands[index] = token;
				index++;
			}
			else
			{
				break;
			}						
		}
	}
	// Now we split up the command to the command and it's options.
	for(index = 0; index < number_of_args; index++)
	{
		first = 1;
		while(1)
		{
			if(first)
			{
				token = strtok(commands[index], " ");
				exec_commands[index] = malloc(sizeof(char*));
				exec_commands[index][0] = token;
				first = 0;
				exec_index = 1;
			}
			else
			{
				token = strtok(NULL, " ");
				if(token != NULL)
				{
					exec_commands[index] = realloc(exec_commands[index], 
						(exec_index + 1) * sizeof(char*));
					exec_commands[index][exec_index] = token;
					exec_index++;
				}
				else
				{
					exec_commands[index] = realloc(exec_commands[index], 
						(exec_index + 1) * sizeof(char*));
					exec_commands[index][exec_index] = 0;
					break;
				}	
			}
		}
	}
}

// function to return the number of '|''s in a string +1.
int countcommands(char *cmd)
{

	int count = 0;
	int number_of_spaces = 0;
	// loop through the string and if two spaces behind each other are found,
	// break.
	for(int i = 0 ; i < 1024 ; i++ )
	{
		if( cmd[i] == '|' ) 
		{
			count++;
		}

		if( cmd[i] == NULL )
		{
			number_of_spaces ++;
			// break off at the second space.
			if(number_of_spaces == 2)
				break;				
		}
	}
	return count;
}

// For every command but the last spawn a process and pipe it's output.
int spawn_proc (int in, int out, char **cmd)
{

	pid_t pid;

	if ((pid = fork()) == 0)
	{
		if (in != STDIN)
		{
			dup2 (in, 0);
			close (in);
		}

		if (out != STDOUT)
		{
			dup2 (out, 1);
			close (out);
		}
		
		// When an error occures in execvp exit.
		if(execvp (cmd[0], cmd) == -1)
		{
			exit(0);
		}
	}
	return pid;
}

// function to loop through the commands and execute them.
void fork_pipes(int number_of_args, char ***cmds)
{
	int index;
	pid_t pid, ppid;
	int in, fd [2];

	ppid = fork();
  	if (ppid == 0) {
		/* The first process gets its input from the original file descriptor 0. */
		in = STDIN;

		/* in the loop all but the last process pipes are spawned.  */
		for(index = 0; index < number_of_args - 1; index++)
		{
			pipe(fd);

			/* fd[STDOUT] is the write from the last process. */
			spawn_proc(in, fd[STDOUT], cmds[index]);

			/* No need for the write and of the pipe, the child will write here.  */
			close(fd[STDOUT]);

			/* Keep the read end of the pipe, the next child will read from there.  */
			in = fd[STDIN];
		}

		/* Last stage of the pipeline - set stdin be the read end of the previous pipe
		and output to the original file descriptor 1(STDOUT). */  
		if (in != STDIN)
		{
			dup2(in, STDIN);
		}

		/* Execute the last stage with the current process. */
		if(execvp(cmds[index][0], cmds[index]) == -1)
		{
			printf("%s", "Execvp ERROR\n");
			exit(0);
		}
	}
	else if (ppid > 0) 
	{
	    /* Parent */
	    waitpid(ppid, NULL,0);
  	}
}

// The handler simply prints a newline.
void handler(int sig_no) 
{
	printf("\n");
}