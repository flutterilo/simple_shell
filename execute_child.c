#include "shell.h"
/**
*execute_child - execute function
*@array_param:array of parameters
*@argv:execute command
*/
void execute_child(char **array_param, char **argv, int command_count)
{
	int status;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid ==  0)
		{
			/* child process */
			if (execve(array_param[0], array_param, NULL) == -1)
			{
				print_string(argv[0]);
				print_string(": ");
				print_int(command_count);
				print_string(": ");
				print_string(array_param[0]);
				print_string(": ");
				print_string("not found\n");
				exit(EXIT_FAILURE);
			}
		}
	else if (child_pid == -1)
	{
		/* error forking */
		perror(argv[0]);
	}
	else
	{
/* parent process */
		wait(&status);
	}
}
