#include "main.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	global_t global[] = { INIT };
	int fd = 2;

	fd +=3;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			perror("Error: reading command");
			exit(127);
			return (EXIT_FAILURE);
		}
		global->readfd = fd;
	}
	populate_env_list(global);
	read_history(global);
	simple_shell(global, av);
	return (EXIT_SUCCESS);
}
