#include "shell.h"

/**
 * main - Entry point of the program.
 * @ac: The number of parameters passed to the executable file. In the case
 * this variable will not be used.
 * @av: The name of the program.
 * Return: Always 0.
 */
int main(__attribute__((unused)) int argc, char **argv)
{
	char *line;
	size_t size;
	int command_count;

	command_count = 0;
	signal(SIGINT, SIG_IGN);
	do {
		command_count++;
		line = NULL;
		size = 0;
		parse_line(line, size, command_count, argv);

	} while (1);

	return (0);
}
