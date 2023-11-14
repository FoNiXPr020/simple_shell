#include "shell.h"

/**
 * custom_strtow - Splits a string into words using custom delimiters
 * @string: The input string
 * @custom_delim: The delimiter string
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **custom_strtow(char *string, char *custom_delim)
{
	int custom_j, i, custom_k, custom_m, custom_numwords = 0;
	char **custom_s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!custom_delim)
		custom_delim = " ";
	for (i = 0; string[i] != '\0'; i++)
	{
		if (!custom_is_delim(string[i], custom_delim) &&
			(custom_is_delim(string[i + 1], custom_delim) || !string[i + 1]))
			custom_numwords++;
	}
	if (custom_numwords == 0)
		return (NULL);
	custom_s = malloc((1 + custom_numwords) * sizeof(char *));
	if (!custom_s)
		return (NULL);
	for (i = 0, custom_j = 0; custom_j < custom_numwords; custom_j++)
	{
		while (custom_is_delim(string[i], custom_delim))
			i++;
		custom_k = 0;
		while (!custom_is_delim(string[i + custom_k],
							custom_delim) && string[i + custom_k])
			custom_k++;
		custom_s[custom_j] = malloc((custom_k + 1) * sizeof(char));
		if (!custom_s[custom_j])
		{
			for (custom_k = 0; custom_k < custom_j; custom_k++)
				free(custom_s[custom_k]);
			free(custom_s);
			return (NULL);
		}
	for (custom_m = 0; custom_m < custom_k; custom_m++)
		custom_s[custom_j][custom_m] = string[i++];
	custom_s[custom_j][custom_m] = 0;
	}
	custom_s[custom_j] = NULL;
	return (custom_s);
}

/**
 * custom_strtow2 - Splits a string into words using a custom delimiter
 * @custom_str: The input string
 * @custom_d: The custom delimiter
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **custom_strtow2(char *custom_str, char custom_d)
{
	int custom_j, i, custom_k, custom_m, custom_numwords = 0;
	char **custom_s;

	if (custom_str == NULL || custom_str[0] == 0)
		return (NULL);
	for (i = 0; custom_str[i] != '\0'; i++)
	{
		if ((custom_str[i] != custom_d && custom_str[i + 1] == custom_d)
		|| (custom_str[i] != custom_d && !custom_str[i + 1])
		|| custom_str[i + 1] == custom_d)
			custom_numwords++;
	}
	if (custom_numwords == 0)
		return (NULL);
	custom_s = malloc((1 + custom_numwords) * sizeof(char *));
	if (!custom_s)
		return (NULL);
	for (i = 0, custom_j = 0; custom_j < custom_numwords; custom_j++)
	{
		while (custom_str[i] == custom_d
		&& custom_str[i] != custom_d)
			i++;
		custom_k = 0;
		while (custom_str[i + custom_k] != custom_d
		&& custom_str[i + custom_k] && custom_str[i + custom_k] != custom_d)
			custom_k++;
		custom_s[custom_j] = malloc((custom_k + 1) * sizeof(char));
		if (!custom_s[custom_j])
		{
			for (custom_k = 0; custom_k < custom_j; custom_k++)
				free(custom_s[custom_k]);
			free(custom_s);
			return (NULL);
		}
		for (custom_m = 0; custom_m < custom_k; custom_m++)
			custom_s[custom_j][custom_m] = custom_str[i++];
		custom_s[custom_j][custom_m] = 0;
	}
	custom_s[custom_j] = NULL;
	return (custom_s);
}

