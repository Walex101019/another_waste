#include "shell.h"
/**
 * print_environment - entry point
 */
void print_environment()
{
	extern char **environ;
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
