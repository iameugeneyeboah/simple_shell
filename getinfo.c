#include "shell.h"

/**
 * clear_info - Initializes fields of the info_t struct to NULL.
 * @info: Pointer to the info_t struct to be cleared.
 *
 * This function sets the fields arg, argv, path, and argc of the info_t struct
 * pointed to by 'info' to NULL.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes fields of the info_t struct.
 * @info: Pointer to the info_t struct to be set.
 * @av: Argument vector from the main function.
 *
 * This fxn initializes the fields fname, argv, path, argc, and other fields
 * of the info_t struct based on given argument vector 'av' and 'arg' field
 * in the info_t struct.
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Frees allocated memory in the info_t struct.
 * @info: Pointer to the info_t struct.
 * @all: 1 if all fields need to be freed, 0 otherwise.
 *
 * This fxn release memory associated with various fields of info_t struct,
 * such as argv, arg, env, history, alias, cmd_buf, environ, and readfd.
 * 'all' parameter tells whether to free all fields or just specific ones.
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

