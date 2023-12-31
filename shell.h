#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_ARG_COUNT 10

int parse_command(char *input, char *args[]);
int execute_command(char *args[], int input_fd, int output_fd);
char *find_command_in_path(const char *command);
void print_environment(void);
void run_pipeline(char *args[]);
void display_prompt(void);
void exit_shell(void);


extern char **environ;

#endif /* SHEL.H */
