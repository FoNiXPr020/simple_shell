#include "shell.h"

/**
 * _exit_shell - Exits the shell.
 * @info: Structure containing potential arguments.
 * Return: Exits with a given exit status (0) if info.argv[0] != "exit".
 */
int _exit_shell(info_t *info)
{
	int iCheck;

	if (info->argv[1])
	{
		iCheck = _convert_to_integer(info->argv[1]);
		if (iCheck == -1)
		{
			info->status = 2;
			display_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eput_char('\n');
			return (1);
		}
		info->err_num = _convert_to_integer(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cd_directory - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _cd_directory(info_t *info)
{
	char *s, *dir, buffer[1024];
	int iChdir;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _get_environ(info, "HOME=");
		if (!dir)
			iChdir =
				chdir((dir = _get_environ(info, "PWD=")) ? dir : "/");
		else
			iChdir = chdir(dir);
	}
	else if (_string_compare(info->argv[1], "-") == 0)
	{
		if (!_get_environ(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_get_environ(info, "OLDPWD=")), _putchar('\n');
		iChdir =
			chdir((dir = _get_environ(info, "OLDPWD=")) ? dir : "/");
	}
	else
		iChdir = chdir(info->argv[1]);
	if (iChdir == -1)
	{
		display_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eput_char('\n');
	}
	else
	{
		_set_env_var(info, "OLDPWD", _get_environ(info, "PWD="));
		_set_env_var(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _display_help - Displays help information.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _display_help(info_t *info)
{
	char **array_args;

	array_args = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*array_args);
	return (0);
}

