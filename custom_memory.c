#include "shell.h"

/**
 * custom_bfree - Frees a pointer and NULLs the address
 * @custom_ptr: Address of the pointer to free
 * Return: 1 if freed, otherwise 0.
 */
int custom_bfree(void **custom_ptr)
{
	if (custom_ptr && *custom_ptr)
	{
		free(*custom_ptr);
		*custom_ptr = NULL;
		return (1);
	}
	return (0);
}

