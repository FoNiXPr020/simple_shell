#include "shell.h"

/**
 * custom_myexit - Exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          a constant function prototype.
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int custom_myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit argument */
	{
		exitcheck = custom_erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			custom_print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = custom_erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * custom_mycd - Changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          a constant function prototype.
 * Return: Always 0
 */
int custom_mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		custom_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = custom_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = custom_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (custom_strcmp(info->argv[1], "-") == 0)
	{
	if (!custom_getenv(info, "OLDPWD="))
	{
		custom_puts(s);
		custom_putchar('\n');
		return (1);
	}
		custom_puts(custom_getenv(info, "OLDPWD=")), custom_putchar('\n');
		chdir_ret = chdir((dir = custom_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
	chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		custom_print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		custom_setenv(info, "OLDPWD", custom_getenv(info, "PWD="));
		custom_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * custom_myhelp - Provides help information (Not yet implemented)
 * @info: Structure containing potential arguments. Used to maintain
 * a constant function prototype.
 * Return: Always 0
 */
int custom_myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	custom_puts("help call works. Function not yet implemented\n");
	if (0)
		custom_puts(*arg_array); /* Temp attribute_unused workaround */
	return (0);
}
