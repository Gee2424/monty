#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Data structure for stack nodes */
typedef struct stack_s
{
int n;
struct stack_s *prev;
struct stack_s *next;
} stack_t;

/* Data structure for opcode instructions */
typedef struct instruction_s
{
char *opcode;
void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/* Function prototypes */
void push(stack_t **stack, unsigned int line_number, const char *arg);
void pall(stack_t **stack, unsigned int line_number);

#endif /* MONTY_H */
