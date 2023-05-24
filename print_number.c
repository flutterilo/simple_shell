#include "shell.h"
/**
 * print_int - Prints an integer to the standard output.
 * @n: The integer to print.
 */
void print_int(int n)
{
	if (n < 0)
	{
		putchar('-');
		n = -n;
	}
	if (n / 10)
		print_int(n / 10);
	print_char((n % 10) + '0');
}
