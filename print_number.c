#include "shell.h"

void print_int(int n)
{
	if (n < 0) {
		putchar('-');
		n = -n;
	}
	if (n/10)
		print_int(n / 10);
	print_char((n % 10) + '0');
}
