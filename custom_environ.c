#include "shell.h"

/**
 * custom_myenv - Prints the current environment.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int custom_myenv(info_t *info)
{
	custom_print_list_str(info->env);
	return (0);
}

/**
 * custom_getenv - Gets the value of an environ variable.
 * @info: Structure containing potential arguments. Used to maintain
 * @name: Env var name.
 * Return: The value.
 */
char *custom_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = custom_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * custom_mysetenv - Initializes a new environment variable
 * or modifies an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int custom_mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (custom_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * custom_myunsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0.
 */
int custom_myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		custom_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populates env linked list.
 * @info: Structure containing potential arguments. Used to maintain
 *                            constant function prototype.
 * Return: Always 0.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		custom_add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

