#include "shell.h"
/**
 * str_len - Computes the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */
int str_len(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}
/**
 * free_array - Frees memory allocated for an array of strings.
 * @arr: The array of strings to free.
 */
void free_array(char **arr)
{
	int index;

	for (index = 0; arr[index] != NULL; index++)
		free(arr[index]);
	free(arr);
}
/**
 * free_f - Frees memory allocated for multiple variables.
 * @n: The number of variables.
 * @...: Variable number of arguments to be freed.
 */
void free_f(int n, ...)
{
	int i;
	char *str;
	va_list a_list;

	va_start(a_list, n);
	for (i = 0; i < n; i++)
	{
		str = va_arg(a_list, char *);
		if (str == NULL)
			str = "(nil)";
		free(str);
	}
	va_end(a_list);
}
/**
 * printing_error - Prints an error message to the standard error output.
 * @av: The name of the program.
 * @count: The line number where the error occurred.
 * @command: The command causing the error.
 */
void printing_error(char *av, int count, char *command)
{
	print_string(av, 1);
	print_string(": ", 1);
	print_int(count);
	print_string(": ", 1);
	print_string(command, 1);
}
/**
 * error_execute - Prints an error message and exits the program.
 * @av: The name of the program.
 * @count: The line number where the error occurred.
 * @tmp_command: The command causing the error.
 */
void error_execute(char *av, int count, char *tmp_command)
{
	printing_error(av, count, tmp_command);
	print_string(": ", 1);
	perror("");
	exit(1);
}
