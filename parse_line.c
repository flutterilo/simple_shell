#include "shell.h"

int parse_line(char *string, size_t cnt, char **argv, int count_command, int *exit_status)
{
	ssize_t count;
	char **arr_tok;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

	count = getline(&string, &cnt, stdin);

	if (count == -1)
	{
			free(string);
			exit(*exit_status);
	}
	else
	{
		arr_tok = arr_token(string);
		if (arr_tok){
			if (built_in_check(argv, string, arr_tok, exit_status, count_command) == 0)
			{
				*exit_status = execute_program(arr_tok, argv, count_command);
			}
		}
		free_comand_array(string, arr_tok);
	}
	return (*exit_status);
}
int count_tokens(char *string)
{
	char *string2;
	char *token;
	char *del = " \n";
	int i;

	string2 = _strdup(string);
	if (string2 == NULL)
		return (-1);
	token = strtok(string2, del);
	for (i = 0; token != NULL; i++)
		token = strtok(NULL, del);
	free(string2);
	return (i);
}

char **arr_token(char *string)
{
	char *del = " \n", *token, *string_copy;
	char **arr_tok;
	int i, j = 0;


	string_copy = _strdup(string);

	i = count_tokens(string);

	if (!i)
	{
		free(string_copy);
		return (NULL);
	}

	arr_tok = malloc(sizeof(char *) * (i + 1));

	if (!arr_tok)
	{
		free(string_copy);
		return (NULL);
	}

	token = strtok(string_copy, del);

	while (token)
	{
		arr_tok[j] = _strdup(token);
		token = strtok(NULL, del);
		j++;
	}
	arr_tok[j] = NULL;
	free(string_copy);

	return (arr_tok);
}

int execute_program(char **arr_tok, char **argv, int count_command)
{
	pid_t child_pid;
	char *path_built;
	int status = 0;

	child_pid = fork();
	if (child_pid == 0)
	{
			path_built = path_finder(arr_tok[0]);
			if (path_built)
			{
					if (execve(path_built, arr_tok, environ) == -1)
					{
						print_error_string(argv[0], arr_tok[0], count_command);
						exit(127);
					}
					free(path_built);
			}
			else
			{
				print_error_string(argv[0], arr_tok[0], count_command);
				exit(127);
			}
	}
	else
	{
		wait(&status);
	}
	return (WEXITSTATUS(status));
}
