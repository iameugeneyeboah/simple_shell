#include "myshell.h"

/**
 * get_environ - Returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: The environment strings array
 */
char **get_environ(myshell_info_t *info)
{
	if (!info->myshell_environ || info->myshell_env_changed)
	{
		info->myshell_environ = myshell_list_to_strings(info->myshell_env);
		info->myshell_env_changed = 0;
	}

	return (info->myshell_environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(myshell_info_t *info, char *var)
{
	myshell_list_t *node = info->myshell_env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = myshell_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->myshell_env_changed = myshell_delete_node_at_index(&(info->myshell_env), i);
			i = 0;
			node = info->myshell_env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->myshell_env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *           or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string env var property
 * @value: The string env var value
 * Return: Always 0
 */
int _setenv(myshell_info_t *info, char *var, char *value)
{
	char *buf = NULL;
	myshell_list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(myshell_strlen(var) + myshell_strlen(value) + 2);
	if (!buf)
		return (1);
	myshell_strcpy(buf, var);
	myshell_strcat(buf, "=");
	myshell_strcat(buf, value);
	node = info->myshell_env;
	while (node)
	{
		p = myshell_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->myshell_env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	myshell_add_node_end(&(info->myshell_env), buf, 0);
	free(buf);
	info->myshell_env_changed = 1;
	return (0);
}
