#include "main.h"

/**
 * _string_dupli - Create a duplicate of a string in memory.
 * @str: Input string
 * Return: Pointer to the newly allocated
 * space in memory containing the copied string.
 */
char *_string_dupli(const char *str)
{
	int i, iLen = 0;
	char *iResult;

	if (str == NULL)
		return (NULL);

	while (str[iLen] != '\0')
		iLen++;

	iResult = (char *)malloc((iLen + 1) * sizeof(char));

	if (iResult == NULL)
		return (NULL);

	for (i = 0; i <= iLen; i++)
		iResult[i] = str[i];

	return (iResult);
}


/**
 * _is_number - Check if a string represents a number.
 * @status: String to be checked
 * Return: None
 */
int _is_number(const char *status)
{
	if (status == NULL || status[0] == '\0')
		return (0);
	while (*status)
	{
		if (!_is_digit(*status))
			return (0);
		status++;
	}
	return (1);
}


/**
 * _is_digit - Check if a character is a digit.
 * @c: Character to be checked
 * Return: 1 if the character is a digit, 0 otherwise
 */
int _is_digit(int c)
{
	return (c >= '0' && c <= '9');
}


