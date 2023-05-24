#include "shell.h"

/**
* built_in - check for builtin commands
* @array_param: array of parameters
* @line: string contain line
* Return: return 1 if exit and 0
*/

int built_in(char **array_param, char *line)
{
	int i = 0;

	builtin_t built_arr[] = {
		{"exit", exit_built},
		{"env", env_built},
		{NULL, NULL}
	};

	while (built_arr[i].built != NULL)
	{
		if (_strcmp(array_param[0], built_arr[i].built) == 0)
		{
			(built_arr[i]).f(array_param, line);
			return (1);
		}
		i++;
	}
	return (0);

}


/**
* exit_built - exit the program
* @array_param: array of parameters
* @line: string contain line
*/

void exit_built(char **array_param, char *line)
{
	int i = 0;

	while (array_param[i])
	{
		free(array_param[i]);
		i++;
	}
	free(array_param);
	free(line);
	exit(1);
}

/**
* env_built - print environment variables
* @array_param: array of parameters
* @line: string contain line
*/

void env_built(char **array_param, char *line)
{
	int i = 0;
	(void) array_param;
	(void) line;

	while (environ[i])
	{
		print_string(environ[i]);
		print_char('\n');
		i++;
	}
}
