#include "shell.h"

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
 * exit_b - Exits the shell. After freeing allocated resources.
 * @line: A string representing the input from the user.
 */
void exit_function(char *line)
{
	free(line);
	exit(EXIT_SUCCESS);
}

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
