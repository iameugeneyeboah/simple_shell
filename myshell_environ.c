#include "myshell.h"

/**
 * myshell_myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int myshell_myenv(myshell_info_t *info)
{
    myshell_print_list_str(info->myshell_env);
    return (0);
}

/**
 * myshell_getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *myshell_getenv(myshell_info_t *info, const char *name)
{
    myshell_list_t *node = info->myshell_env;
    char *p;

    while (node)
    {
	p = myshell_starts_with(node->str, name);
	if (p && *p)
	return (p);
	node = node->next;
    }
    return (NULL);
}

/**
 * myshell_mysentenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int myshell_mysetenv(myshell_info_t *info)
{
    if (info->myshell_argc != 3)
    {
	myshell_eputs("Incorrect number of arguments\n");
	return (1);
    }
    if (mysetenv(info, info->myshell_argv[1], info->myshell_argv[2]))
	return (0);
    return (1);
}

/**
 * myshell_myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int myshell_myunsetenv(myshell_info_t *info)
{
    int i;

    if (info->myshell_argc == 1)
    {
	myshell_eputs("Too few arguments.\n");
	return (1);
    }
    for (i = 1; i <= info->myshell_argc; i++)
	myshell_unsetenv(info, info->myshell_argv[i]);

    return (0);
}

/**
 * myshell_populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int myshell_populate_env_list(myshell_info_t *info)
{
    myshell_list_t *node = NULL;
    size_t i;

    for (i = 0; myshell_environ[i];)
	myshell_add_node_end(&node, myshell_environ[i], 0);
	info->myshell_env = node;
    return (0);
}
