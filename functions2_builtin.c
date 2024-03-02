#include "main.h"

/**
 * cd_builtin - Change directory.
 * @d: Data struct input
 * Return: Void
 */

void cd_builtin(data *d)
{
	char *i_dir = d->vr_arry[1];
	char i_cwd[256];

	if (getcwd(i_cwd, sizeof(i_cwd)) == NULL)
		perror("getcwd() error");
	_set_env(d, "PWD", i_cwd);
	if (!i_dir)
		i_dir = _fetchenv("HOME");
	if (chdir(i_dir) == -1)
		perror("cd");
	else
	{
		_set_env(d, "OLDPWD", _fetchenv("PWD"));
		if (getcwd(i_cwd, sizeof(i_cwd)) == NULL)
			perror("getcwd() error");
		_set_env(d, "PWD", i_cwd);
	}
}
