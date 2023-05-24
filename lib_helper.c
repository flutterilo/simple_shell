#include "shell.h"
/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: An integer less than, equal to, or greater than zero if s1 is found
 * respectively, to be less than, to match, or be greater than s2.
 */
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

/**
 * _strdup - Duplicates a string.
 * @src: The source string to be duplicated.
 * Return: A pointer to the duplicated string,
 * or NULL if memory allocation fails.
 */
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

/**
 * print_string - Prints a string to the standard output.
 * @str: The string to be printed.
 * @new_line: A flag indicating whether to print a new line after the string.
 */
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
 * print_char - Writes a character to the standard output.
 * @c: The character to be written.
 * Return: Upon success, the number of characters written.
 */

int print_char(char c)
{
	return (write(1, &c, 1));
}
