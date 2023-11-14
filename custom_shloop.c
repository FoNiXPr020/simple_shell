#include "shell.h"

/**
 * hsh - Main shell loop
 * @info: The parameter & return info_t struct
 * @av: The argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t custom_r = 0;
	int custom_builtin_ret = 0;

	while (custom_r != -1 && custom_builtin_ret != -2)
	{
		custom_clear_info(info);
		if (custom_interactive(info))
			custom_puts("$ ");
		_eputchar(BUF_FLUSH);
		custom_r = custom_get_input(info);
		if (custom_r != -1)
		{
			custom_set_info(info, av);
			custom_builtin_ret = custom_find_builtin(info);
			if (custom_builtin_ret == -1)
				custom_find_cmd(info);
		}
		else if (custom_interactive(info))
			custom_putchar('\n');
		custom_free_info(info, 0);
	}
	custom_write_history(info);
	custom_free_info(info, 1);
	if (!custom_interactive(info) && info->status)
		exit(info->status);
	if (custom_builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (custom_builtin_ret);
}

/**
 * custom_find_builtin - Finds a builtin command
 * @info: The parameter & return info_t struct
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int custom_find_builtin(info_t *info)
{
	int custom_i, custom_builtin_ret = -1;
	custom_builtin_table custom_builtintbl[] = {
		{"exit", custom_myexit},
		{"env", custom_myenv},
		{"help", custom_myhelp},
		{"history", custom_myhistory},
		{"setenv", custom_mysetenv},
		{"unsetenv", custom_myunsetenv},
		{"cd", custom_mycd},
		{"alias", custom_myalias},
		{NULL, NULL}
	};

	for (custom_i = 0; custom_builtintbl[custom_i].type; custom_i++)
		if (custom_strcmp(info->argv[0], custom_builtintbl[custom_i].type) == 0)
		{
			info->line_count++;
			custom_builtin_ret = custom_builtintbl[custom_i].func(info);
			break;
	}
	return (custom_builtin_ret);
}

/**
 * custom_find_cmd - Finds a command in PATH
 * @info: The parameter & return info_t struct
 * Return: void
 */
void custom_find_cmd(info_t *info)
{
	char *custom_path = NULL;
	int custom_i, custom_k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (custom_i = 0, custom_k = 0; info->arg[custom_i]; custom_i++)
		if (!custom_is_delim(info->arg[custom_i], " \t\n"))
			custom_k++;
	if (!custom_k)
		return;

	custom_path = custom_find_path(info,
			custom_getenv(info, "PATH="), info->argv[0]);
	if (custom_path)
	{
		info->path = custom_path;
		custom_fork_cmd(info);
	}
	else
	{
		if ((custom_interactive(info) || custom_getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && custom_is_cmd(info, info->argv[0]))
			custom_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			custom_print_error(info, "not found\n");
		}
	}
}

/**
 * custom_fork_cmd - Forks an exec thread to run a command
 * @info: The parameter & return info_t struct
 * Return: void
 */
void custom_fork_cmd(info_t *info)
{
	pid_t custom_child_pid;

	custom_child_pid = fork();
	if (custom_child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (custom_child_pid == 0)
	{
		if (execve(info->path, info->argv, custom_get_environ(info)) == -1)
		{
			custom_free_info(info, 1);
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
				custom_print_error(info, "Permission denied\n");
		}
	}
}

