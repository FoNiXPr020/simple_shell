#include "main.h"

/**
 * _fetchenv - Retrieve the value of a specified environment variable.
 * @name: Name of the environment variable
 * Return: Value of the environment variable
 */
char *_fetchenv(char *name)
{
	int i = -1;
	size_t iLen;

	if (name == NULL || *name == '\0')
		return (NULL);
	if (environ == NULL)
		return (NULL);

	iLen = _string_len(name);

	while (environ[++i])
	{
		if (!_string_com_limit(environ[i], name, iLen) && environ[i][iLen] == '=')
		{
			return (environ[i] + iLen + 1);
		}
	}
	return (NULL);
}

/**
 * _search_executable - Search for the executable file
 * associated with a given command.
 * @d: Name of the command
 * Return: None
 */
int _search_executable(data *d)
{
	char *iToken, *iPath,
		*iPaths = malloc(_string_len(_fetchenv("PATH") ?
		_fetchenv("PATH") : "") + 1);
	size_t token_len;
	int iFind = -1;

	if (!_fetchenv("PATH"))
		goto step_out;
	_string_copy(iPaths, _fetchenv("PATH"));
	if (iPaths == NULL)
		goto step_out;
	iToken = strtok(iPaths, ":");
	while (iToken)
	{
		token_len = _string_len(iToken) + _string_len(d->vr_arry[0]) + 2;
		iPath = malloc(token_len);
		if (iPath == NULL)
			return (iFind);
		_string_copy(iPath, iToken);
		_string_concat(iPath, "/");
		_string_concat(iPath, d->vr_arry[0]);
		if (access(iPath, F_OK) == 0)
		{
			free(d->vr_arry[0]);
			d->vr_arry[0] = _string_dupli(iPath);
			free(iPath);
			iFind = 0;
			break;
		}
		free(iPath);
		iToken = strtok(NULL, ":");
	}
step_out:
	free(iPaths);
	return (iFind);
}

/**
 * establish_variable - Create or modify an environment variable.
 * @name: Name of the variable
 * @value: Value of the variable
 * Return: None
 */
char *establish_variable(char *name, char *value)
{
	size_t iLen = strlen(name) + strlen(value) + 2;
	char *new_entry = malloc(iLen);

	if (new_entry == NULL)
		return (NULL);

	strcpy(new_entry, name);
	strcat(new_entry, "=");
	strcat(new_entry, value);

	return (new_entry);
}

/**
 * _update_environment - Create or modify an environment variable.
 * @name: Name of the variable
 * @value: Value of the variable
 * Return: None
 */
char **_update_environment(char *name, char *value)
{
	int len_env = 0, i = 0;
	char *new_ent;
	char **new_env;

	while (environ[len_env])
		len_env++;
	new_ent = establish_variable(name, value);
	if (new_ent == NULL)
		return (NULL);
	new_env = _fetchenv(name) ? malloc((len_env + 1) * sizeof(char *))
								: malloc((len_env + 2) * sizeof(char *));

	if (!new_env)
	{
		free(new_ent);
		return (NULL);
	}
	for (i = 0; environ[i]; i++)
	{
		new_env[i] = malloc(strlen(environ[i]) + 1);
		if (!new_env[i])
		{
			release_pointers(new_env);
			free(new_ent);
			return (NULL);
		}
		if (strncmp(environ[i], name, strlen(name)) == 0
		&& environ[i][strlen(name)] == '=')
			strcpy(new_env[i], new_ent);
		else
			strcpy(new_env[i], environ[i]);
	}
	if (!_fetchenv(name))
	{
		new_env[len_env] = new_ent;
		new_env[len_env + 1] = NULL;
	}
	else
		new_env[len_env] = NULL;
	return (new_env);
}

/**
 * _set_env - Create or modify an environment variable.
 * @d: Flag to indicate the action
 * @name: Name of the variable
 * @value: Value of the variable
 * Return: None
 */
int _set_env(data *d, char *name, char *value)
{
	char **iNew;

	if (!name || !value)
		return (-1);

	iNew = _update_environment(name, value);
	if (!iNew)
		return (-1);
	environ = iNew;
	d->flag_setenv = 1;

	return (0);
}

