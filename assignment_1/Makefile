#Set the C compiler.
CC = gcc

# Set the flags for the C compiler.
CFLAGS = -Wall -std=c99 -pedantic
LDLIBS = -lm

# Macro for compiling .
COMPILE = $(CC) $(CFLAGS) -c

# Macro for the output of compilation.
OUTPUT = -o $@

# Rule for creating an object file by compiling a c file.
# ’%’ is a wildcard meaning any file with the suffix ’.c’ will be
# compiled.
%.o: %.c
	$(COMPILE) $(LDLIBS) $< $(OUTPUT)

# Rule for building an executable called ‘main ’ using test.o
main: test.o
	$(CC) $(CFLAGS) $(OUTPUT) $ˆ