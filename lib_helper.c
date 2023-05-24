#include "shell.h"

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			break;
		}
		i++;
	}
	return (s1[i] - s2[i]);
}

char *_strdup(char *src)
{
	int i = 0;
	int len;
	char *dest;

	len = str_len(src);
	dest = malloc(sizeof(char) * (len + 1));

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void print_string(char *str, int new_line)
{
	int i;

	if (str == NULL)
		str = "(null)";
	for (i = 0; str[i] != '\0'; i++)
		write(STDOUT_FILENO, &str[i], 1);
	if (new_line == 0)
		write(STDOUT_FILENO, "\n", 1);
}

/**
 * _write_char - Writes a character to stdout
 * @c: Character that will be written to stdout
 * Return: Upon success how many characters were written.
 */
int print_char(char c)
{
	return (write(1, &c, 1));
}
