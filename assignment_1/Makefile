#Set program name.
PROGNAME = assignment1

#Set the C compiler.
CC = gcc

# Set the flags for the C compiler.
CFLAGS = -Wall -std=c99 -pedantic -lm

# Macro for compiling .
COMPILE = $(CC) $(CFLAGS) -c

# Macro for the output of compilation.
OUTPUT =  $(PROGNAME)

# Rule for creating an object file by compiling a c file.
# the file with the name ’assignment1.c’ will be compiled.
object: assignment1.c
	$(COMPILE) $(PROGNAME).c $(OUTPUT)

# Rule for building an executable called ‘main’ using assignment1.o
main: assignment1.o
	$(CC) $(CFLAGS) $(OUTPUT)