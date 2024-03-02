#include "shell.h"

/**
 * _copy_string_n - Copy a string up to a specified number of characters.
 * @dest: The destination string to copy to
 * @src: The source string
 * @n: The number of characters to copy
 * Return: The concatenated string
 */

char *_copy_string_n(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _cat_strings_n - Concatenate two strings
 * up to a specified number of bytes.
 * @dest: The first string
 * @src: The second string
 * @n: The maximum number of bytes to use
 * Return: The concatenated string
 */

char *_cat_strings_n(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _find_character - Locate a character in a string.
 * @s: The string to be parsed
 * @c: The character to look for
 * Return: A pointer to the memory area s containing the character c
 */
char *_find_character(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

