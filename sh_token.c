#include "shell.h"

/**
 * split_string - Splits a string into words. Repeat delimiters are ignored.
 * @str: The input string.
 * @d: The delimiter string.
 * Return: A pointer to an array of strings, or NULL on failure.
 */

char **split_string(char *str, char *d)
{
	int i, j, k, m, iNum = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimiter(str[i], d) && (is_delimiter(str[i + 1], d) || !str[i + 1]))
			iNum++;

	if (iNum == 0)
		return (NULL);
	s = malloc((1 + iNum) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < iNum; j++)
	{
		while (is_delimiter(str[i], d))
			i++;
		k = 0;
		while (!is_delimiter(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

