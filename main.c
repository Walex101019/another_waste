#include "shell.h"
/**
 * main - entry point
 *
 * Return: Returns
 */
int main(void)
{
	char input[MAX_INPUT_LENGTH];
	char *args[MAX_ARG_COUNT + 1];
	char *path;
	int arg_count;

	while (1)
	{
		display_prompt();
		if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
		{
			printf("\nExiting shell.\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		arg_count = parse_command(input, args);
		if (arg_count < 0)
		{
			continue;
		}
		if (strcmp(args[0], "env") == 0)
		{
			print_environment();
		}
		else if (strcmp(args[0], "exit") == 0)
		{
			printf("Exiting shell.\n");
			break;
		}
		else
		{
			if (strchr(input, '|'))
			{
				run_pipeline(args);
			}
			else
			{
				path = find_command_in_path(args[0]);
				if (path)
				{
					args[0] = path;
					if (execute_command(args, STDIN_FILENO, STDOUT_FILENO) == -1)
					{
						printf("Command execution failed: %s\n", args[0]);
					}
					free(path);
				}
				else
				{
					printf("command not found: %s\n", args[0]);
				}
			}
		}
	}
	return (0);
}
