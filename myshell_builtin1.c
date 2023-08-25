#include "myshell.h"

/**
 * myshell_history - Displays the history list, one command per line, preceded
 *                   with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int myshell_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * myshell_unset_alias - Unsets an alias
 * @info: Parameter struct
 * @str: The string alias
 * Return: Always 0 on success, 1 on error
 */
int myshell_unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = myshell_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * myshell_set_alias - Sets an alias
 * @info: Parameter struct
 * @str: The string alias
 * Return: Always 0 on success, 1 on error
 */
int myshell_set_alias(info_t *info, char *str)
{
	char *p;

	p = myshell_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (myshell_unset_alias(info, str));

	myshell_unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string
 * @node: The alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = myshell_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			myshell_putchar(*a);
		myshell_putchar('\'');
		myshell_puts(p + 1);
		myshell_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * myshell_alias - Mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int myshell_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = myshell_strchr(info->argv[i], '=');
		if (p)
			myshell_set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}