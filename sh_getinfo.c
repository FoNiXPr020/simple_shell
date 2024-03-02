#include "shell.h"

/**
 * initialize_info - Initializes the info_t struct.
 * @info: Address of the info_t struct to initialize.
 */
void initialize_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * initialize_info_arg - Initializes the
 * info_t struct with arguments.
 * @info: Address of the info_t struct to initialize.
 * @av: Argument vector.
 */
void initialize_info_arg(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = split_string(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		substitute_aliases(info);
		substitute_variables(info);
	}
}

/**
 * release_info - Frees the fields of the info_t struct.
 * @info: Address of the info_t struct.
 * @all: True if freeing all fields, otherwise false.
 */
void release_info(info_t *info, int all)
{
	free_string_array(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			deallocate_list(&(info->env));
		if (info->history)
			deallocate_list(&(info->history));
		if (info->alias)
			deallocate_list(&(info->alias));
		free_string_array(info->environ);
			info->environ = NULL;
		free_and_nullify((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFFER_FLUSH);
	}
}

