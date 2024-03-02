#include "shell.h"

/**
 * run_shell - Main shell loop.
 * @info: The parameter & return info struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int run_shell(info_t *info, char **av)
{
	ssize_t r = 0;
	int ret_builtin = 0;

	while (r != -1 && ret_builtin != -2)
	{
		initialize_info(info);
		if (inter_active(info))
			_puts("$ ");
		_eput_char(BUFFER_FLUSH);
		r = get_input_newline(info);
		if (r != -1)
		{
			initialize_info_arg(info, av);
			ret_builtin = search_builtin(info);
			if (ret_builtin == -1)
				search_command(info);
		}
		else if (inter_active(info))
			_putchar('\n');
		release_info(info, 0);
	}
	create_or_append_history(info);
	release_info(info, 1);
	if (!inter_active(info) && info->status)
		exit(info->status);
	if (ret_builtin == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (ret_builtin);
}

/**
 * search_builtin - Find a builtin command.
 * @info: The parameter & return info struct.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *        -2 if builtin signals exit().
 */
int search_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _exit_shell},
		{"env", _environ_print},
		{"help", _display_help},
		{"history", _display_history},
		{"setenv", _set_environ},
		{"unsetenv", _unset_environ},
		{"cd", _cd_directory},
		{"alias", _handle_shell_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_string_compare(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * search_command - Find a command in PATH.
 * @info: The parameter & return info struct.
 *
 * Return: Void.
 */
void search_command(info_t *info)
{
	char *iPath = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	iPath = search_in_path(info, _get_environ(info, "PATH="), info->argv[0]);
	if (iPath)
	{
		info->path = iPath;
		fork_execute(info);
	}
	else
	{
		if ((inter_active(info) || _get_environ(info, "PATH=")
			|| info->argv[0][0] == '/') && check_command(info, info->argv[0]))
			fork_execute(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			display_error(info, "not found\n");
		}
	}
}

/**
 * fork_execute - Forks an exec thread to run a command.
 * @info: The parameter & return info struct.
 *
 * Return: Void.
 */
void fork_execute(info_t *info)
{
	pid_t pid_child;

	pid_child = fork();
	if (pid_child == -1)
	{
		perror("Error:");
		return;
	}
	if (pid_child == 0)
	{
		if (execve(info->path, info->argv, copy_environment(info)) == -1)
		{
			release_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				display_error(info, "Permission denied\n");
		}
	}
}

