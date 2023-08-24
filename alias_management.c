#include "shell.h"

/**
 * print_alias - add, remove or show aliases
 * @data: struct for the data of the program
 * @alias: name of the alias to be printed
 * Return: zero if a success else other number if declared in the arguments
 */
int print_alias(data_of_program *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (str_compare(data->alias_list[i], alias, alias_length)
				&&	data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, remove or show aliases
 * @data: structure for the program data
 * @name: requested alias name
 * Return: zero if a success else any other number if declared in the arguments
 */
char *get_alias(data_of_program *data, char *name)
{
	int i, alias_length;

	/* validates the arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{/* checks through the environ for coincidence of the var name */
		if (str_compare(name, data->alias_list[i], alias_length) &&
			data->alias_list[i][alias_length] == '=')
		{/* returns the value of the key NAME=  when found */
			return (data->alias_list[i] + alias_length + 1);
		}
	}
	/* returns NULL if not found */
	return (NULL);

}

/**
 * set_alias - add alias
 * @alias_string: set alias in the form (name='value')
 * @data: structure for the data
 * Return: zero when successful, or any other number if declared in the argument
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* validates the argument */
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/* find = char */
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{/* search through to see if the value of the alias is another */
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	/* checks for coincidence of the var name */
	for (j = 0; data->alias_list[j]; j++)
		if (str_compare(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{/* if the alias exist */
			free(data->alias_list[j]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* if the alias exist */
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else /* if  and only if the alias does not exist */
		data->alias_list[j] = str_duplicate(alias_string);
	return (0);
}
