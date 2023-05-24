#include "shell.h"
/**
*parse_line -parsing command
*@argv:content of arguments
*@line:command line
*@n:length
*/
void parse_line(char **argv, char *line, size_t n, int command_count)
{
	ssize_t check;
	char **array_param;
	int i = 0;
	(void) command_count;

	if (isatty(STDIN_FILENO))
		print_string(PROMPT);

	check = getline(&line, &n, stdin);
	if (check == -1)
	{
		free(line);
		exit(1);
	}
	else
	{
		while (line[i] != '\n')
			i++;
		line[i] = '\0';
		if (_strcmp(line, "exit") == 0)
		{
			free(line);
			exit(1);
		}
		array_param = tokenization(line);
		if (array_param[0] == NULL)
		{
			free(array_param);
			free(line);
			return;
		}
		execute_child(array_param, argv, command_count);
		i = 0;
		while (array_param[i])
		{
			free(array_param[i]);
			i++;
		}
		free(array_param);
		free(line);
	}

}

/**
 * tokenization - split string into tokens
 * @line: string base
 * Return: return array of tokens
 */


char **tokenization(char *line)
{
	char *str_copy;
	char **array_param;
	char *token;
	int length = 0;
	int i = 0;

	str_copy = _strdup(line);
	length = count_tokens(str_copy);
	if (length == -1)
	{
		free(str_copy);
		return (NULL);
	}
	array_param = malloc((sizeof(char *)) * (length + 1));
	if (array_param == NULL)
	{
		free(str_copy);
		return (NULL);
	}
	token = strtok(str_copy, DELIM_PROMPT);

	while (token != NULL)
	{
		array_param[i] = _strdup(token);
		token = strtok(NULL, DELIM_PROMPT);
		i++;
	}
	array_param[i] = NULL;
	free(str_copy);
	return (array_param);
}

/**
* count_tokens - get number of tokens in string
* @str_copy: string base
* Return: return number of tokens
*/

int count_tokens(char *str_copy)
{
	char *token, *str_copy_up;
	int length = 0;

	str_copy_up = _strdup(str_copy);
	if (str_copy_up == NULL)
		return (-1);
	token = strtok(str_copy_up, DELIM_PROMPT);

	while (token != NULL)
	{
		token = strtok(NULL, DELIM_PROMPT);
		length++;
	}
	free(str_copy_up);
	return (length);
}
