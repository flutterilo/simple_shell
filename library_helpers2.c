#include "shell.h"

void print_string(char *str)
{
	if (str)
		write(STDOUT_FILENO, str, _strlen(str));
	else
		write(STDOUT_FILENO, "(null)", 6);

}

void print_integer(int n)
{
	char c;

	if (n  == 0)
		return;
	print_integer(n / 10);
	c = (n % 10) + '0';
	write(STDERR_FILENO, &c, 1);

}

void print_int(int n)
{
	int check;
	char number;

	if (n < 10)
	{
		print_char(n + '0');
		return;
	}
	for (check = 10; (n / check) > 9; check *= 10)
  {}
	while (check > 0)
	{
		number = ((n / check) % 10) + '0';
		write(STDERR_FILENO, &number, 1);
		check /= 10;
	}
}

void print_char(char c)
{
	write(STDOUT_FILENO, &c, 1);
}

