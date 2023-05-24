#include "shell.h"

int str_len(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void free_array(char **arr)
{
	int index;

	for (index = 0; arr[index] != NULL; index++)
		free(arr[index]);
	free(arr);
}

void free_f(int n, ...)
{
	int i;
	char *str;
	va_list a_list;

	va_start(a_list, n);
	for (i = 0; i < n; i++)
	{
		str = va_arg(a_list, char*);
		if (str == NULL)
			str = "(nil)";
		free(str);
	}
	va_end(a_list);
}


void printing_error(char *av, int count, char *command)
{
	print_string(av, 1);
	print_string(": ", 1);
	print_int(count);
	print_string(": ", 1);
	print_string(command, 1);
}


void error_execute(char *av, int count, char *tmp_command)
{
	printing_error(av, count, tmp_command);
	print_string(": ", 1);
	perror("");
	exit(1);
}
