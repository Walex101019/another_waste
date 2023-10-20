#include "shell.h"
/**
 * execute_command - entry point
 * @args: arguement passed
 * @input_fd: arguement passed
 * @output_fd: arguement passed
 * Return: Returns -1
 */
int execute_command(char *args[], int input_fd, int output_fd)
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
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (output_fd != STDOUT_FILENO)
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
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

/**
 * run_pipeline - entry point
 * @args: arguemnet passed
 */
void run_pipeline(char *args[])
{
	int num_cmds = 0;
	char *pipeline[MAX_ARG_COUNT + 1];
	char *token = strtok(args[0], "|");
	int pipefds[2];
	int input_fd = STDIN_FILENO;
	int input_redirect_fd;
	int status;
	int output_redirect_fd;
	char *cmd_args[MAX_ARG_COUNT + 1];
	int arg_count;
	int i;

	while (token != NULL)
	{
		pipeline[num_cmds++] = token;
		token = strtok(NULL, "|");
		if (num_cmds >= MAX_ARG_COUNT)
		{
			printf("Too many commands in the pipeline. Maximum allowed: %d\n", MAX_ARG_COUNT);
			return;
		}
	}
	for (i = 0; i < num_cmds; i++)
	{
		if (i < num_cmds - 1)
		{
			if (pipe(pipefds) < 0)
			{
				perror("Pipe creation failed");
				exit(1);
			}
		}
		arg_count = parse_command(pipeline[i], cmd_args);
		if (arg_count < 0)
		{
			continue;
		}
		input_redirect_fd = (i == 0) ? input_fd : pipefds[0];
		output_redirect_fd = (i == num_cmds - 1) ? STDOUT_FILENO : pipefds[1];
		status = execute_command(cmd_args, input_redirect_fd, output_redirect_fd);
		if (i < num_cmds - 1)
		{
			close(pipefds[0]);
		}
		if (status != 0)
		{
			printf("Command failed with exit status: %d\n", status);
			return;
		}
	}
}
