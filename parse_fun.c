#include "shell.h"


void parse_line(char *line, size_t n, int command_count, char **argv)
{
	int i;
	ssize_t read_len;
	int token_count;
	char **param_array;
	const char *delim = "\n\t ";

	token_count = 0;
	write(STDOUT_FILENO, PROMPT, str_len(PROMPT));
	read_len = getline(&line, &n, stdin);
	if (read_len != -1)
	{
		param_array = tokenization(line, delim, token_count);
		if (param_array[0] == NULL)
		{
			free_f(2, param_array, line);
			return;
		}
		i = built_in(param_array, line);
		if (i == -1)
			create_child(param_array, line, command_count, argv);
		for (i = 0; param_array[i] != NULL; i++)
			free(param_array[i]);
		free_f(2, param_array, line);
	}
	else
		exit_function(line);
}

void create_child(char **param_array, char *line, int count, char **argv)
{
	pid_t id;
	int check, i, status;
	struct stat st;
	char *tp_command, *command;

	id = fork();
	if (id == 0)
	{
		tp_command = param_array[0];
		command = find_path_command(param_array[0]);
		if (command == NULL)
		{
			check = stat(tp_command, &st);
			if (check == -1)
			{
				printing_error(argv[0], count, tp_command);
				print_string(": not found", 0);
				free_f(2, line, tp_command);
				for (i = 1; param_array[i]; i++)
					free(param_array[i]);
				free(param_array);
				exit(100);
			}
			command = tp_command;
		}
		param_array[0] = command;
		if (param_array[0] != NULL)
		{
			if (execve(param_array[0], param_array, environ) == -1)
				error_execute(argv[0], count, tp_command);
		}
	}
	else
		wait(&status);
}

char **tokenization(char *line, const char *delim, int token_count)
{
	char **param_array;

	token_count = count_token(line, delim);
	if (token_count == -1)
	{
		free(line);
		return (NULL);
	}
	param_array = tokenize_line(token_count, line, delim);
	if (param_array == NULL)
	{
		free(line);
		return (NULL);
	}

	return (param_array);
}

char **tokenize_line(int token_count, char *line, const char *delim)
{
	int i;
	char **array_param;
	char *token;
	char *line_cp;

	line_cp = _strdup(line);
	array_param = malloc(sizeof(char *) * (token_count + 1));
	if (array_param == NULL)
		return (NULL);
	token = strtok(line_cp, delim);
	for (i = 0; token != NULL; i++)
	{
		array_param[i] = _strdup(token);
		token = strtok(NULL, delim);
	}
	array_param[i] = NULL;
	free(line_cp);
	return (array_param);
}

int count_token(char *line, const char *delim)
{
	char *str;
	char *token;
	int i;

	str = _strdup(line);
	if (str == NULL)
		return (-1);
	token = strtok(str, delim);
	for (i = 0; token != NULL; i++)
		token = strtok(NULL, delim);
	free(str);
	return (i);
}
