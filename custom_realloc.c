#include "shell.h"

/**
 * custom_memset - Fills memory with a constant byte
 * @custom_s: The pointer to the memory area
 * @custom_b: The byte to fill *s with
 * @custom_n: The amount of bytes to be filled
 * Return: A pointer to the memory area s
 */
char *custom_memset(char *custom_s, char custom_b, unsigned int custom_n)
{
	unsigned int custom_i;

	for (custom_i = 0; custom_i < custom_n; custom_i++)
		custom_s[custom_i] = custom_b;
	return (custom_s);
}

/**
 * custom_ffree - Frees a string of strings
 * @custom_pp: The string of strings
 */
void custom_ffree(char **custom_pp)
{
	char **custom_a = custom_pp;

	if (!custom_pp)
		return;
	while (*custom_pp)
		free(*custom_pp++);
	free(custom_a);
}

/**
 * custom_realloc - Reallocates a block of memory
 * @pnt: Pointer to the previous malloc'ated block
 * @size_old: Byte size of the previous block
 * @size_new: Byte size of the new block
 * Return: Pointer to the old block if successful, or NULL on failure
 */
void *custom_realloc(void *pnt, unsigned int size_old, unsigned int size_new)
{
	char *custom_p;

	if (!pnt)
		return (malloc(size_new));
	if (!size_new)
		return (free(pnt), NULL);
	if (size_new == size_old)
		return (pnt);

	custom_p = malloc(size_new);
	if (!custom_p)
		return (NULL);

	size_old = size_old < size_new ? size_old : size_new;
	while (size_old--)
		custom_p[size_old] = ((char *)pnt)[size_old];
	free(pnt);
	return (custom_p);
}

