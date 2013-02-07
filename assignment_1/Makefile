#Set program name.
PROGNAME = assignment1

#Set the C compiler.
CC = gcc

# Set the flags for the C compiler.
CFLAGS = -Wall -std=c99 -pedantic -lm 

# Macro for compiling .
COMPILE = $(CC) $(CFLAGS) -c

# Macro for the output of compilation.
OUTPUT = -o  $@

# Rule for creating an object file by compiling a c file.
# the file with the name ’assignment1.c’ will be compiled.
$(PROGNAME).o: $(PROGNAME).c
	$(COMPILE) $< $(OUTPUT)

# Rule for building an executable called ‘$(PROGNAME)’ using assignment1.o
$(PROGNAME): $(PROGNAME)
	$(CC) $(CFLAGS) $(OUTPUT) $(PROGNAME)
