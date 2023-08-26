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
	/* Implementation details */
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
	/* Implementation details */
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
	/* Implementation details */
}
