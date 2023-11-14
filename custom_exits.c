#include "shell.h"

/**
 * custom_strncpy - Copies a source string to a
 * destination buffer with a limit
 * @custom_dest: The destination buffer
 * @custom_src: The source string
 * @n: The maximum number of characters to copy
 * Return: Pointer to the destination buffer
*/
char *custom_strncpy(char *custom_dest, char *custom_src, int n)
{
	int custom_i, custom_j;
	char *custom_s = custom_dest;

	custom_i = 0;
	while (custom_src[custom_i] != '\0' && custom_i < n - 1)
	{
		custom_dest[custom_i] = custom_src[custom_i];
		custom_i++;
	}
	if (custom_i < n)
	{
		custom_j = custom_i;
		while (custom_j < n)
		{
			custom_dest[custom_j] = '\0';
			custom_j++;
		}
	}
	return (custom_s);
}

/**
 * custom_strncat - Concatenates two strings with a limit on te
 * number of bytes
 * @custom_dest: The first string
 * @custom_src: The second string
 * @n: The maximum number of bytes to use from the source
 *
 * Return: Pointer to the concatenated string
 */
char *custom_strncat(char *custom_dest, char *custom_src, int n)
{
	int custom_i, custom_j;
	char *custom_s = custom_dest;

	custom_i = 0;
	custom_j = 0;
	while (custom_dest[custom_i] != '\0')
		custom_i++;
	while (custom_src[custom_j] != '\0' && custom_j < n)
	{
		custom_dest[custom_i] = custom_src[custom_j];
		custom_i++;
		custom_j++;
	}
	if (custom_j < n)
		custom_dest[custom_i] = '\0';
	return (custom_s);
}

/**
 * custom_strchr - Locates a character in a string
 * @custom_s: The string to be parsed
 * @custom_c: The character to look for
 * Return: A pointer to the memory area in the string
 */
char *custom_strchr(char *custom_s, char custom_c)
{
	do {
		if (*custom_s == custom_c)
			return (custom_s);
	} while (*custom_s++ != '\0');

	return (NULL);
}

