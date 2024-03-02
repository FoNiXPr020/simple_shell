#include "main.h"

/**
 * _string_len - Calculate the number of characters in a string.
 * @str: Input string
 * Return: Number of characters in the string.
 */

unsigned int _string_len(char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
		;
	return (i);
}


/**
 * _string_compare - Compare two strings.
 * @s1: Input constant string 1
 * @s2: Input constant string 2
 * Return: An integer indicating the result of the comparison:
 *         - 0 if s1 and s2 are equal
 *         - A negative value if s1 is less than s2
 *         - A positive value if s1 is greater than s2
 */

int _string_compare(const char *s1, const char *s2)
{
	int i;
	int rese = 0;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
		{
			rese = s1[i] - s2[i];
			break;
		}
	}

	return (rese);
}

/**
 * _string_com_limit - Compare two strings up
 * to a specified number of characters.
 * @s1: Input constant string 1
 * @s2: Input constant string 2
 * @n: Number of characters to compare
 * Return: An integer indicating the result of the comparison:
 *         - 0 if s1 and s2 are equal up to n characters
 *         - A negative value if s1 is less than s2
 *         - A positive value if s1 is greater than s2
 */

int _string_com_limit(const char *s1, const char *s2, int n)
{
	int i;
	int rese = 0;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{

		if (i >= n)
			break;
		if (s1[i] != s2[i])
		{
			rese = s1[i] - s2[i];
			break;
		}
	}

	return (rese);
}

/**
 * _string_copy - Copy the contents of one string to another.
 * @dest: Destination character array
 * @src: Source constant character array
 * Return: A pointer to the destination character array.
 */

char *_string_copy(char *dest, const char *src)
{
	int iLen;

	for (iLen = 0; src[iLen] != '\0'; ++iLen)
	{
		dest[iLen] = src[iLen];
	}
	dest[iLen] = '\0';
	return (dest);
}

/**
 * _string_concat - Append the contents of one string to another.
 * @dest: Destination string
 * @src: Source constant string
 * Return: None
 */

char *_string_concat(char *dest, const char *src)
{
	char *iResult = dest;

	while (*dest != '\0')
		dest++;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';

	return (iResult);
}
