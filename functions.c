#include "main.h"

/**
 * _printf - Display a string to the standard output.
 * @str: Input string
 * Return: None
 */
void _printf(const char *str)
{
	if (!str)
		return;
	while (*str)
	{
		write(STDOUT_FILENO, str, 1);
		str++;
	}
}

/**
 * release_pointers - Deallocate memory used by an array of pointers.
 * @array: Array of pointers
 * Return: None
 */
void release_pointers(char **array)
{
	int i;

	if (!array)
		return;

	for (i = 0; array[i]; i++)
	{
		free(array[i]);
		array[i] = NULL;
	}

	free(array);
}

/**
 * parse_string - Split a given string by a specified delimiter.
 * @d: Input data structure
 * @delim: Delimiter string
 * Return: None
 */
void parse_string(data *d, const char *delim)
{
	char *iToken;
	int i = 0;

	d->vr_arry = malloc(2 * sizeof(char *));
	if (d->vr_arry == NULL)
	{
		free(d->cmd);
		perror(d->shell_name);
		exit(EXIT_FAILURE);
	}
	d->vr_arry[0] = NULL;
	d->vr_arry[1] = NULL;

	iToken = strtok(d->cmd, delim);
	while (iToken)
	{
		d->vr_arry = realloc(d->vr_arry, (i + 2) * sizeof(char *));
		if (d->vr_arry == NULL)
			goto free;
		d->vr_arry[i] = _string_dupli(iToken);
		if (d->vr_arry[i] == NULL)
			goto free;
		i++;
		iToken = strtok(NULL, delim);
	}
	d->vr_arry[i] = NULL;
	return;
free:
	release_pointers(d->vr_arry);
	free(d->cmd);
	perror(d->shell_name);
	exit(EXIT_FAILURE);
}

/**
 * initialize_data - Initialize data structures.
 * @d: Input data structure
 * @shell_name: Name of the shell
 * Return: None
 */

void initialize_data(data *d, const char *shell_name)
{
	d->cmd = NULL;
	d->vr_arry = NULL;
	d->shell_name = shell_name;
	d->last_exit_status = EXIT_SUCCESS;
	d->flag_setenv = 0;
}

/**
 * retrieve_command - Obtain the command from
 * the prompt and structure it into a data structure.
 * @d: Input data structure
 * Return: None
 */
void retrieve_command(data *d)
{
	size_t n = 0;
	ssize_t iRead;
	int i = 0;

	iRead = _custom_getline(&d->cmd, &n, stdin);

	if (iRead == -1)
	{
		free(d->cmd);
		_printf("\n");
		exit(EXIT_SUCCESS);
	}

	d->cmd[iRead - 1] = '\0';
	_trim_string(d->cmd);

	for (i = 0; d->cmd[i] != '\0'; i++)
	{
		if (d->cmd[0] == '#' || (d->cmd[i] == '#' && d->cmd[i - 1] == ' '))
		{
			d->cmd[i] = '\0';
			break;
		}
	}
	_trim_string(d->cmd);
}

