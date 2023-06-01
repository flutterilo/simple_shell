#include "shell.h"

char *path_finder(char *program)
{
	char *path_value, *path_name, *token, *path_with_slash;

	path_name  = _getenv("PATH");
	path_value = strtok(NULL, "=");
	if (is_file_exist(program) == 0)
		return (_strdup(program));
	token = strtok(path_value, ":");
	while (token)
	{
		path_with_slash = build_path_slash(token, program);
		if (is_file_exist(path_with_slash) == 0)
		{
			free(path_name);
			return (path_with_slash);
		}
		token = strtok(NULL, ":");
		free(path_with_slash);
	}
	free(path_name);
	return (NULL);
}


char *_getenv(char *name)
{
	int i = 0;
	char *env_name;
	char *token;

	while (environ[i])
	{
		env_name = _strdup(environ[i]);
		token = strtok(env_name, "=");
		if (_strcmp(token, name) == 0)
		{
			return (env_name);
		}
		free(env_name);
		i++;
	}
	return (NULL);
}

int is_file_exist(char *path)
{
	return (access(path, R_OK));
}

char *build_path_slash(char *str1, char *str2)
{
	int i = 0, j = 0;
	char *path_string;

	if (!str1 || !str2)
		return (NULL);
	path_string = malloc(sizeof(char) + _strlen(str1) + _strlen(str2) + 2);

	while (str1[i])
	{
		path_string[i] = str1[i];
		i++;
	}
	path_string[i] = '/';
	i++;
	while (str2[j])
	{
		path_string[i + j] = str2[j];
		j++;
	}
	path_string[i + j] = '\0';
	return (path_string);
}
