#include "shell.h"

void print_error_string(char *name, char *command, int count_command)
{
	print_error(name);
	print_error(": ");
	print_integer(count_command);
	print_error(": ");
	print_error(command);
	print_error(": ");
	print_error("not found\n");
}

void print_error(char *str)
{
	if (!str)
		write(STDERR_FILENO, "(null)", 6);
	write(STDERR_FILENO, str, _strlen(str));
}



void free_comand_array(char *string, char **arr_tok)
{
	int j = 0;

	while (arr_tok[j])
	{
		free(arr_tok[j]);
		j++;
	}
	free(arr_tok);
	free(string);
}
