#include "shell.h"

/**
 * custom_strcpy - Copies a source string to a destination buffer
 * @custom_dest: The destination buffer
 * @custom_src: The source string
 * Return: Pointer to the destination buffer
 */
char *custom_strcpy(char *custom_dest, char *custom_src)
{
	int custom_i = 0;

	if (custom_dest == custom_src || custom_src == 0)
		return (custom_dest);
	while (custom_src[custom_i])
	{
		custom_dest[custom_i] = custom_src[custom_i];
		custom_i++;
	}
	custom_dest[custom_i] = 0;
	return (custom_dest);
}

/**
 * custom_strdup - Duplicates a source string and allocates memory for it
 * @custom_str: The source string to duplicate
 * Return: Pointer to the duplicated string
*/
char *custom_strdup(const char *custom_str)
{
	int custom_length = 0;
	char *custom_ret;

	if (custom_str == NULL)
		return (NULL);
	while (*custom_str++)
		custom_length++;
	custom_ret = malloc(sizeof(char) * (custom_length + 1));
	if (!custom_ret)
		return (NULL);
	for (custom_length++; custom_length--;)
		custom_ret[custom_length] = *--custom_str;
	return (custom_ret);
}

/**
 * custom_puts - Prints an input string to standard output
 * @custom_str: The string to be printed
 * Return: Nothing
 */
void custom_puts(char *custom_str)
{
	int custom_i = 0;

	if (!custom_str)
		return;
	while (custom_str[custom_i] != '\0')
	{
		custom_putchar(custom_str[custom_i]);
		custom_i++;
	}
}

/**
 * custom_putchar - Writes a character to standard output
 * @custom_c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar(char custom_c)
{
	static int custom_i;
	static char custom_buf[CUSTOM_WRITE_BUFFER_SIZE];

	if (custom_c == BUF_FLUSH || custom_i >= CUSTOM_WRITE_BUFFER_SIZE)
	{
		write(1, custom_buf, custom_i);
		custom_i = 0;
	}
	if (custom_c != BUF_FLUSH)
		custom_buf[custom_i++] = custom_c;
	return (1);
}

