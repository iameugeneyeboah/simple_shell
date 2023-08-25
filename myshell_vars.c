#include "myshell.h"

/**
 * myshell_is_chain - Tests if the current character in buffer is a chain delimiter
 * @info: The parameter struct
 * @buf: The character buffer
 * @p: Address of the current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int myshell_is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = '\0';
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = '\0';
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = '\0'; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * myshell_check_chain - Checks if we should continue chaining based on last status
 * @info: The parameter struct
 * @buf: The character buffer
 * @p: Address of the current position in buf
 * @i: Starting position in buf
 * @len: Length of buf
 *
 * Return: Void
 */
void myshell_check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = '\0';
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = '\0';
			j = len;
		}
	}

	*p = j;
}

/**
 * myshell_replace_alias - Replaces aliases in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int myshell_replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = myshell_node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = myshell_strchr(node->str, '=');
		if (!p)
			return (0);
		p = myshell_strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * myshell_replace_vars - Replaces variables in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int myshell_replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!myshell_strcmp(info->argv[i], "$?"))
		{
			myshell_replace_string(&(info->argv[i]),
					myshell_strdup(myshell_convert_number(info->status, 10, 0)));
			continue;
		}
		if (!myshell_strcmp(info->argv[i], "$$"))
		{
			myshell_replace_string(&(info->argv[i]),
					myshell_strdup(myshell_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = myshell_node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			myshell_replace_string(&(info->argv[i]),
					myshell_strdup(myshell_strchr(node->str, '=') + 1));
			continue;
		}
		myshell_replace_string(&info->argv[i], myshell_strdup(""));

	}
	return (0);
}

/**
 * myshell_replace_string - Replaces string
 * @old: Address of the old string
 * @new: New string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int myshell_replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
