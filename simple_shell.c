#include "shell.h"



int main(__attribute__((unused)) int argc, char **argv)
{
	char *string = NULL;
	int exit_status = 0;
	size_t cnt = 0;
	int count_command = 0;

	while (1)
	{
		string = NULL;
		cnt = 0;
		count_command++;
		exit_status = parse_line(string, cnt, argv, count_command, &exit_status);
	}

	return (exit_status);
}
