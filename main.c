#include "shell.h"

/**
 * main - Main function, entry point of the program.
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t sh_info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eput_char('\n');
				_eput_char(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		sh_info->readfd = fd;
	}
	initialize_environ(sh_info);
	read_history_from_file(sh_info);
	run_shell(sh_info, av);
	return (EXIT_SUCCESS);
}

