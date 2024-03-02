#include "shell.h"

/**
 * inter_active - returns true if shell is inter_active mode
 * @info: struct address
 *
 * Return: 1 if inter_active mode, 0 otherwise
 */
int inter_active(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 * Return: 1 if true, 0 if false.
 */
int is_delimiter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * is_alphabetic - Checks for an alphabetic character.
 * @c: The character to check.
 * Return: 1 if c is alphabetic, 0 otherwise.
 */

int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi_conv - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: 0 if no numbers in string, converted number otherwise.
 */

int _atoi_conv(char *s)
{
	int i, iSign = 1, iFlag = 0, iOutput;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && iFlag != 2; i++)
	{
		if (s[i] == '-')
			iSign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			iFlag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (iFlag == 1)
			iFlag = 2;
	}

	if (iSign == -1)
		iOutput = -result;
	else
		iOutput = result;

	return (iOutput);
}


