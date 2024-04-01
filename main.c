#include "monty.h"

/**
* main - Entry point for the Monty bytecode interpreter.
* @argc: Number of command line arguments.
* @argv: Array of command line arguments.
* Return: EXIT_SUCCESS on success, or EXIT_FAILURE on failure.
*/
int main(int argc, char *argv[])
{
FILE *file;
char *line = NULL;
size_t len = 0;
ssize_t read;
unsigned int line_number = 0;
stack_t *stack = NULL;

if (argc != 2)
{
fprintf(stderr, "USAGE: monty file\n");
exit(EXIT_FAILURE);
}

file = fopen(argv[1], "r");
if (file == NULL)
{
fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
exit(EXIT_FAILURE);
}

while ((read = getline(&line, &len, file)) != -1)
{
line_number++;
parse_line(line, line_number, &stack);
}

free(line);
fclose(file);
free_stack(&stack);
return (EXIT_SUCCESS);
}

/**
* parse_line - Parses a line from a Monty bytecode file and executes the opcode.
* @line: The line to parse.
* @line_number: The current line number in the file.
* @stack: Double pointer to the top of the stack.
*/
void parse_line(char *line, unsigned int line_number, stack_t **stack)
{
char *opcode;
char *arg;

opcode = strtok(line, " \t\n");
if (opcode == NULL || opcode[0] == '#')  // '#' denotes a comment line.
{
return;
}

arg = strtok(NULL, " \t\n");

if (strcmp(opcode, "push") == 0)
{
if (arg == NULL || !is_integer(arg))
{
fprintf(stderr, "L%d: usage: push integer\n", line_number);
exit(EXIT_FAILURE);
}
push(stack, line_number, arg);
}
else if (strcmp(opcode, "pall") == 0)
{
pall(stack, line_number);
}
else
{
fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
exit(EXIT_FAILURE);
}
}

/**
* is_integer - Checks if a string is an integer.
* @str: The string to check.
* Return: 1 if string is an integer, 0 otherwise.
*/
int is_integer(char *str)
{
if (*str == '-' || *str == '+') str++;  // Handle negative/positive signs.

if (!*str) return 0;  // Empty string is not an integer.

while (*str)
{
if (!isdigit((unsigned char)*str))
return 0;
str++;
}

return 1;
}

/**
* Implement other necessary functions here, such as `push`, `pall`, and `free_stack`.
*/
