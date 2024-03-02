#include "main.h"

/**
 * _print_error - Display an error message on stderr.
 * @str1: Name of the shell program
 * @str2: Error message to display
 * Return: None
 */
void _print_error(const char *str1, const char *str2)
{
	if (!str1 || !str2)
		return;

	while (*str1)
	{
		write(STDERR_FILENO, str1, 1);
		str1++;
	}

	write(STDERR_FILENO, ": ", 2);

	while (*str2)
	{
		write(STDERR_FILENO, str2, 1);
		str2++;
	}
	write(STDERR_FILENO, "\n", 1);
}


/**
 * _trim_string - Remove leading and trailing spaces and tabs from a string.
 * @str: Input string
 * Return: None
 */

void _trim_string(char *str)
{
	int i, j, iLen = _string_len(str);

	for (i = 0; i < iLen && (str[i] == ' ' || str[i] == '\t'); i++)
		;

	for (j = 0; i < iLen ; i++, j++)
		str[j] = str[i];

	str[j] = '\0';

	for (i = _string_len(str) - 1; i > 0
	&& (str[i] == ' ' || str[i] == '\t'); i--)
		str[i] = '\0';
}


/**
 * _realloc - Reallocate memory using malloc and free.
 * @ptr: Void pointer
 * @new_size: New size of memory block (unsigned integer)
 * Return: Newly allocated memory
 */
void *_realloc(void *ptr, unsigned int new_size)
{
	char *p;
	unsigned int i, tp = new_size, old_size = sizeof(ptr);

	if (old_size == new_size)
		return (ptr);
	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size > old_size)
		tp = old_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	p = malloc(new_size);

	for (i = 0; i < tp; i++)
		p[i] = ((char *)ptr)[i];
	free(ptr);
	return (p);
}

