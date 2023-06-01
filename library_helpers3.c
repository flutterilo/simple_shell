#include "shell.h"

/**
 * _isalpha - check if character or not
 * @c: take int parameter
 * Return: return 1 if succes- 0 if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}
