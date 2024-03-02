#include "main.h"

/**
 * builtin_exec - Check if a command is a
 * built-in function and execute it if so.
 * @d: Data struct input
 * Return: 1 if the command is built-in, 0 otherwise.
 */
int builtin_exec(data *d)
{
	int i = 0;
	builtin builtin[] = {
		{"exit", exit_builtin},
		{"env", env_builtin},
		{"setenv", setenv_builtin},
		{"unsetenv", unsetenv_builtin},
		{"cd", cd_builtin},
		{NULL, NULL},
	};

	for (i = 0; builtin[i].cmd; i++)
	{
		if (_string_compare(d->vr_arry[0], builtin[i].cmd) == 0)
		{
			builtin[i].f(d);
			return (1);
		}
	}
	return (0);
}

/**
 * exit_builtin - Exit the shell.
 * @d: Data struct input
 * Return: Void
 */
void exit_builtin(data *d)
{
	const char *error = "./hsh: 1: exit: Illegal number: ";

	if (d->vr_arry[1])
	{
		if (d->vr_arry[1][0] != '-' && _is_number(d->vr_arry[1]))
			d->last_exit_status = atoi(d->vr_arry[1]);
		else
		{
			write(STDERR_FILENO, error, strlen(error));
			write(STDERR_FILENO, d->vr_arry[1], strlen(d->vr_arry[1]));
			write(STDERR_FILENO, "\n", 1);
			d->last_exit_status = 2;
		}
	}
	release_pointers(d->vr_arry);
	free(d->cmd);
	if (d->flag_setenv)
		release_pointers(environ);
	exit(d->last_exit_status);
}

/**
 * env_builtin - Print the current environment.
 * @d: Data struct input
 * Return: Void
 */
void env_builtin(data *d)
{
	int i = 0;

	(void)d;
	while (environ[i])
	{
		_printf(environ[i]);
		_printf("\n");
		i++;
	}
}
/**
 * setenv_builtin - Initialize a new environment
 * variable or modify an existing one.
 * @d: Data struct input
 * Return: Void
 */

void setenv_builtin(data *d)
{
	(void)d;
	if (d->vr_arry[1] && d->vr_arry[2])
	{
		if (_set_env(d, d->vr_arry[1], d->vr_arry[2]) == -1)
		{
			perror("setenv");
		}
	}
}

/**
 * unsetenv_builtin - Remove an environment variable.
 * @d: Data struct input
 * Return: Void
 */
void unsetenv_builtin(data *d)
{
	int i, j;
	int len;

	(void)d;
	if (!d->vr_arry[1] || !getenv(d->vr_arry[1]))
	{
		_print_error(d->shell_name, "variable not found.");
		return;
	}
	len = strlen(d->vr_arry[1]);
	for (i = 0; environ[i]; i++)
		if (strncmp(environ[i], d->vr_arry[1], len) == 0 && environ[i][len] == '=')
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];
}
