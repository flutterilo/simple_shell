#include "shell.h"
/**
 * cd_function - Handles the "cd" (change directory) command.
 * @line: A string representing the input command line.
 */
void cd_function(char *line)
{
	int index;
	int token_count;
	char **param_array;
	const char *delim = "\n\t ";

	token_count = 0;
	param_array = tokenization(line, delim, token_count);
	if (param_array[0] == NULL)
	{
		free_f(2, param_array, line);
		return;
	}
	if (param_array[1] == NULL)
	{
		index = find_path("HOME");
		chdir((environ[index]) + 5);
	}
	else if (_strcmp(param_array[1], "-") == 0)
		print_string(param_array[1], 0);

	else
		chdir(param_array[1]);
	free_array(param_array);
}

/**
 * env_function - Prints the environment variables.
 * @line: A string representing the input command line.
 */
void env_function(__attribute__((unused))char *line)
{
	int i;
	int j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '\0'; j++)
			write(STDOUT_FILENO, &environ[i][j], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * exit_function - Exits the shell, freeing allocated resources.
 * @line: A string representing the input command line.
 */
void exit_function(char *line)
{
	free(line);
	exit(2);
}
/**
 * check_builtin - Checks if a command is a built-in command.
 * @str: The command to check.
 * Return: A func ptr to the built in function, or NULL if not found.
 */
void (*check_builtin(char *str))(char *str)
{
	int i;

	builtin_t buildin[] = {
		{"exit", exit_function},
		{"env", env_function},
		{"cd", cd_function},
		{NULL, NULL}
	};

	for (i = 0; buildin[i].built != NULL; i++)
	{
		if (_strcmp(str, buildin[i].built) == 0)
		{
			return (buildin[i].f);
		}
	}
	return (NULL);
}
/**
 * built_in - Executes a built-in command.
 * @command: An array of strings representing the command and its arguments.
 * @line: A string representing the input command line.
 * Return: 0 if the command is a built in and executed , -1 otherwise.
 */

int built_in(char **command, char *line)
{
	void (*build)(char *);

	build = check_builtin(command[0]);
	if (build == NULL)
		return (-1);
	if (_strcmp("exit", command[0]) == 0)
		free_array(command);
	build(line);
	return (0);
}
