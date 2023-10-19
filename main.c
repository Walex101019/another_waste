#include "shell.h"
/**
 * main - entry point
 *
 * Return: Returns
 */
int main()
{
	char input[MAX_INPUT_LENGTH];
	char *args[MAX_ARG_COUNT + 1];
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
			if (execute_command(args) == -1)
			{
				printf("Command not found: %s\n", args[0]);
			}
		}
	}
	return (0);
}
