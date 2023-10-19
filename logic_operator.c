#include "shell.h"
/**
 * execute_command - entry point
 * @args: arguement passed
 * Return: Returns -1
 */
int execute_command(char *args[])
{
	pid_t child_pid = fork();
	int status;

	if (child_pid < 0)
	{
		perror("Fork failed");
		return (-1);
	}
	else if (child_pid == 0)
	{
		execvp(args[0], args);
		perror("Command execution failed");
		exit(1);
	}
	else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
		else
		{
			printf("Error executing command\n");
			return (-1);
		}
	}
}

/**
 * parse_command - entry point
 * @input: args passed
 * @args: arguement passed
 * Return: Returns arg_count
 */
int parse_command(char *input, char *args[])
{
	int arg_count = 0;
	char *token = strtok(input, " ");

	while (token != NULL)
	{
		args[arg_count++] = token;
		token = strtok(NULL, " ");
		if (arg_count >= MAX_ARG_COUNT)
		{
			printf("Too many arguments. Maximum allowed: %d\n", MAX_ARG_COUNT);
			return (-1);
		}
	}
	args[arg_count] = NULL;
	return (arg_count);
}
