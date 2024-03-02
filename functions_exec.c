#include "main.h"

/**
 * initiate_process - Begin execution of a new process.
 * @d: Input data structure
 * Returns: None
 */

void initiate_process(data *d)
{
	pid_t i_child_pid = fork();
	int sta = 0;

	if (i_child_pid == -1)
		goto free;
	if (i_child_pid == 0 && execve(d->vr_arry[0], d->vr_arry, NULL) == -1)
		goto free;
	else if (wait(&sta) == -1)
		goto free;
	if (WIFEXITED(sta))
		d->last_exit_status = WEXITSTATUS(sta);
	return;
free:
	perror(d->shell_name);
	release_pointers(d->vr_arry);
	free(d->cmd);
	exit(EXIT_FAILURE);
}

/**
 * handle_interrupt - Manage interrupt signals.
 * @signal: Input interrupt signal
 * Returns: None
 */

void handle_interrupt(int signal)
{
	(void)signal;
	_printf("\n");
	exit(EXIT_FAILURE);
}

/**
 * execute_command - Run a command.
 * @d: Input data structure
 * Returns: None
 */

void execute_command(data *d)
{
	const char cmd_prompt[] = PROMPT;

	signal(SIGINT, handle_interrupt);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			_printf(cmd_prompt);

		retrieve_command(d);
		if (_string_len(d->cmd) != 0)
		{
			parse_string(d, " ");
			if (!builtin_exec(d))
			{
				_search_executable(d);
				if (access(d->vr_arry[0], F_OK) == -1)
				{
					perror(d->shell_name);
				}
				else
				{
					initiate_process(d);
				}
			}
			release_pointers(d->vr_arry);
		}
		free(d->cmd);
	}
}
