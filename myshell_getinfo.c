#include "myshell.h"

/**
 * clear_info - Initializes info_t struct
 * @info: Struct address
 */
void clear_info(myshell_info_t *info)
{
	info->myshell_arg = NULL;
	info->myshell_argv = NULL;
	info->myshell_path = NULL;
	info->myshell_argc = 0;
}

/**
 * set_info - Initializes info_t struct
 * @info: Struct address
 * @av: Argument vector
 */
void set_info(myshell_info_t *info, char **av)
{
	int i = 0;

	info->myshell_fname = av[0];
	if (info->myshell_arg)
	{
		info->myshell_argv = myshell_strtow(info->myshell_arg, " \t");
		if (!info->myshell_argv)
		{
			info->myshell_argv = malloc(sizeof(char *) * 2);
			if (info->myshell_argv)
			{
				info->myshell_argv[0] = myshell_strdup(info->myshell_arg);
				info->myshell_argv[1] = NULL;
			}
		}
		for (i = 0; info->myshell_argv && info->myshell_argv[i]; i++)
			;
		info->myshell_argc = i;

		myshell_replace_alias(info);
		myshell_replace_vars(info);
	}
}

/**
 * free_info - Frees info_t struct fields
 * @info: Struct address
 * @all: True if freeing all fields
 */
void free_info(myshell_info_t *info, int all)
{
	free(info->myshell_argv);
	info->myshell_argv = NULL;
	info->myshell_path = NULL;
	if (all)
	{
		if (!info->myshell_cmd_buf)
			free(info->myshell_arg);
		if (info->myshell_env)
			myshell_free_list(&(info->myshell_env));
		if (info->myshell_history)
			myshell_free_list(&(info->myshell_history));
		if (info->myshell_alias)
			myshell_free_list(&(info->myshell_alias));
		free(info->myshell_environ);
			info->myshell_environ = NULL;
		free((void **)info->myshell_cmd_buf);
		if (info->myshell_readfd > 2)
			close(info->myshell_readfd);
		myshell_putchar(MYSHELL_BUF_FLUSH);
	}
}
