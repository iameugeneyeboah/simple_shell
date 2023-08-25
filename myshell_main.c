#include "myshell.h"

/**
 * main - Entry point
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	myshell_info_t myshell[] = { MYSHELL_INFO_INIT };
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
				puts(av[0]);
				puts(": 0: Can't open ");
				puts(av[1]);
				putchar('\n');
				putchar(MYSHELL_BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		myshell->myshell_readfd = fd;
	}
	myshell_populate_env_list(myshell);
	myshell_read_history(myshell);
	myshell_mycd(myshell);
	return (EXIT_SUCCESS);
}
