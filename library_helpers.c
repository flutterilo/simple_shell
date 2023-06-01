#include "shell.h"

int _strlen(char *string)
{
        int n = 0;

        while (string[n])
        {
                n++;
        }

        return (n);
}

char *_strdup(char *string)
{
        char *string2;
        int m, i;

        m = _strlen(string);

        string2 = malloc(sizeof(char) * (m + 1));

        if (string2 == NULL)
        {
                return (NULL);
        }

        for (i = 0; string[i]; i++)
        {
                string2[i] = string[i];
        }

        string2[i] = '\0';

        return (string2);
}

int _strcmp(char *str1, char *str2)
{
	int i = 0;

	while (str1[i])
	{
		if (str1[i] != str2[i])
			return str1[i] - str2[i];
		i++;
	}
	return (0);

}


/**
 * _atoi - converts a string to an integer
 * @s: string to be converted
 * Return: the int converted from the string
 */
int _atoi(char *s)
{
	int res = 0;
	int sign = 1;
	int i = 0;

	if (s[0] == '-') {
		sign = -1;

		i++;
	}

	for (; s[i] != '\0'; ++i)
		res = res * 10 + s[i] - '0';

	return sign * res;
}
