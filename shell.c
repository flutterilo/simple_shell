#include "shell.h"
/**
* main - simple shell
*@argc:number of arguments
*@argv:content of arguments
*Return:return 0
*/
int main(__attribute__((unused)) int argc, char **argv)
{
	char *line;
	size_t n = 0;
	int command_count = 0;

	/*signal(SIGINT, SIG_IGN);*/
	while (1)
	{
		line = NULL;
		n = 0;
		command_count++;
		parse_line(argv, line, n, command_count);
	}
	return (0);
}
