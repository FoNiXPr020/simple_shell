#include "main.h"

/**
 * main - init data
 * @argc: input size of @argv
 * @argv: input array of command line arguments
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	data d;
	(void)argc;
	initialize_data(&d, argv[0]);
	execute_command(&d);

	return (0);
}

