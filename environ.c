#include "shell.h"

/**
 * _environ_print - Prints the current environment.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _environ_print(info_t *info)
{
	print_string_list(info->env);
	return (0);
}

/**
 * _get_environ - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 * Return: The value of the environment variable.
 */
char *_get_environ(info_t *info, const char *name)
{
	list_t *iNode = info->env;
	char *p;

	while (iNode)
	{
		p = check_prefix(iNode->str, name);
		if (p && *p)
			return (p);
		iNode = iNode->next;
	}
	return (NULL);
}

/**
 * _set_environ - Initializes a new environment variable
 *                             or modifies an existing one.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _set_environ(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_env_var(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _unset_environ - Removes an environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */

int _unset_environ(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_remove_env_var(info, info->argv[i]);

	return (0);
}

/**
 * initialize_environ - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int initialize_environ(info_t *info)
{
	list_t *iNode = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		append_node(&iNode, environ[i], 0);
	info->env = iNode;
	return (0);
}

