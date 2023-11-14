#include "shell.h"

/**
 * _eputs - Prints an input string to stderr.
 * @str: The string to be printed.
 * Return: Nothing.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
	{
		return;
	}

	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Writes the character 'c' to stderr.
 * @c: The character to print.
 * Return: On success 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[CUSTOM_WRITE_BUFFER_SIZE];

	if (c == BUF_FLUSH || i >= CUSTOM_WRITE_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
	}

	return (1);
}

/**
 * custom_putfd - Writes the character 'c' to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 * Return: On success 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int custom_putfd(char c, int fd)
{
	static int i;
	static char buf[CUSTOM_WRITE_BUFFER_SIZE];

	if (c == BUF_FLUSH || i >= CUSTOM_WRITE_BUFFER_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
	}

	return (1);
}

/**
 * custom_putsfd - Prints an input string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 * Return: The number of characters written.
 */
int custom_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
	{
		return (0);
	}

	while (*str)
	{
		i += custom_putfd(*str++, fd);
	}

	return (i);
}

