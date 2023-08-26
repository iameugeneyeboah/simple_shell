#include "shell.h"

/**
 * main - Entry point of the shell program.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * This function initializes the 'info' struct, handles file redirection,
 * populates the environment list, reads history, and invokes the shell loop.
 *
 * Return: Returns 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };  /* Initialize the 'info' struct */
	int fd = 2;

	/* Inline assembly to manipulate file descriptor */
	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	/* Check if an input file is provided */
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
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;  /* Set the read file descriptor */
	}

	populate_env_list(info); /* Populate the environment list */
	read_history(info); /* Read history from file */
	hsh(info, av); /* Invoke the shell loop */
	return (EXIT_SUCCESS);
}
