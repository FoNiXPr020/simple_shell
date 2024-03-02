#include "shell.h"

/**
 * _eputs - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eput_char(str[i]);
		i++;
	}
}

/**
 * _eput_char - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int _eput_char(char c)
{
	static int i;
	static char iBuffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, iBuffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		iBuffer[i++] = c;
	return (1);
}

/**
 * _put_fd - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int _put_fd(char c, int fd)
{
	static int i;
	static char iBuffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(fd, iBuffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		iBuffer[i++] = c;
	return (1);
}

/**
 * _puts_fd - Prints an input string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters put.
 */
int _puts_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _put_fd(*str++, fd);
	}
	return (i);
}

