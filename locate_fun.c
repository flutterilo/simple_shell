#include "shell.h"

char *find_path_command(char *command)
{
	char *str = "PATH";
	char *constructed;
	char **path_tokens;
	int index;
	char *directory;

	index = find_path(str);
	path_tokens = tokenize_path(index, str);
	if (path_tokens == NULL)
		return (NULL);

	directory = search_directories(path_tokens, command);
	if (directory == NULL)
	{
		free_array(path_tokens);
		return (NULL);
	}

	constructed = build_path(directory, command);
	if (constructed == NULL)
	{
		free_array(path_tokens);
		return (NULL);
	}

	free_array(path_tokens);

	return (constructed);
}

int find_path(char *str)
{
	int i;
	int len;
	int j;

	len = str_len(str);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
		{
			if (environ[i][j] != str[j])
				break;
		}
		if (j == len && environ[i][j] == '=')
			return (i);
	}
	return (-1);
}

char **tokenize_path(int index, char *str)
{
	char *env_value;
	int token_count;
	const char *delim = ":\n";
	char **path_tokens;
	int len;

	len = str_len(str);
	token_count = 0;
	env_value = environ[index] + (len + 1);
	path_tokens = tokenization(env_value, delim, token_count);
	if (path_tokens == NULL)
		return (NULL);

	return (path_tokens);
}

char *search_directories(char **path_tokens, char *command)
{
	int i, s;
	char *cwd;
	char *str;
	size_t size;
	struct stat stat_buf;

	str = NULL;
	size = 0;
	cwd = getcwd(str, size);
	if (cwd == NULL)
		return (NULL);
	if (command[0] == '/')
		command = command + 1;
	for (i = 0; path_tokens[i] != NULL; i++)
	{
		s = chdir(path_tokens[i]);
		if (s == -1)
		{
			return (NULL);
		}
		s = stat(command, &stat_buf);
		if (s == 0)
		{
			chdir(cwd);
			free(cwd);
			return (path_tokens[i]);
		}
	}
	chdir(cwd);
	free(cwd);
	return (NULL);
}

char *build_path(char *directory, char *command)
{
	int i, j;
	int dir_len;
	int command_len;
	int length;
	char *built;

	if (directory == NULL || command == NULL)
		return (NULL);
	dir_len = str_len(directory) + 1;
	command_len = str_len(command) + 1;
	length = dir_len + command_len;

	built = malloc(sizeof(char) * length);
	if (built == NULL)
		return (NULL);

	for (i = 0; i < length; i++)
	{
		for (j = 0; directory[j] != '\0'; j++, i++)
			built[i] = directory[j];
		built[i] = '/';
		i++;
		for (j = 0; command[j] != '\0'; j++, i++)
			built[i] = command[j];
	}
	built[--i] = '\0';
	return (built);
}
