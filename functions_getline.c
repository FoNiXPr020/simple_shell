#include "main.h"

/**
 * _helper_getline - Auxiliary function for the getline function.
 * @lineptr: Input string
 * @n: Input integer
 * Return: An integer
 */
int _helper_getline(char **lineptr, size_t *n)
{
	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	return (0);
}

/**
 * _custom_getline - Read input from a file stream.
 * @lineptr: Input string
 * @n: Input integer
 * @stream: Input file stream
 * Return: A ssize_t value
 */
ssize_t _custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t bytesRead = 0;
	size_t iPos = 0, iNewSize;
	static char iBuff[READ_BUF_SIZE];
	static size_t iBuffSize, iBuffPos;
	char *iNewBuffer;

	if (lineptr == NULL || n == NULL || stream == NULL
		|| _helper_getline(lineptr, n) == -1)
		return (-1);
	while (1)
	{
		if (iBuffPos >= iBuffSize)
		{
			bytesRead = read(stream->_fileno, iBuff, READ_BUF_SIZE);
			if (bytesRead <= 0 && iPos == 0)
				return (-1);
			else if (bytesRead <= 0)
				break;
			iBuffSize = bytesRead;
			iBuffPos = 0;
		}
		if (iPos >= *n - 1)
		{
			iNewSize = *n * 2;
			iNewBuffer = realloc(*lineptr, iNewSize);
			if (iNewBuffer == NULL)
				return (-1);
			*lineptr = iNewBuffer;
			*n = iNewSize;
		}
		(*lineptr)[iPos++] = iBuff[iBuffPos++];
		if ((*lineptr)[iPos - 1] == '\n')
			break;
	}
	(*lineptr)[iPos] = '\0';
	return (iPos);
}
