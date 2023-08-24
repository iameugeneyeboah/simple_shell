#include "shell.h"

/**
 * env_get_key - gets the value of an env var
 * @key: the env var of interest
 * @data: data struct of the program
 * Return: a pointer to the value of the var or NULL if it doesn't exist
 */
char *env_get_key(char *key, data_of_program *data)
{
	int i, key_length = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains the length of the var requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* check for coincidence */
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (data->env[i] + key_length + 1);
		}
	}
	/* returns NULL if not found */
	return (NULL);
}

/**
 * env_set_key - overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: name of var to be set
 * @value: new value
 * @data: data structure of the program
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int i, key_length = 0, is_new_key = 1;

	/* validate the arg */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtains the length of the var requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* check for coincidence */
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* If the key already exists */
			is_new_key = 0;
			/* free the entire var as it is newly created below */
			free(data->env[i]);
			break;
		}
	}
	/* do a string with the form key=value */
	data->env[i] = str_concat(str_duplicate(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (is_new_key)
	{/* if the variable is new create it at end of actual list */
	/* to put the NULL value in the next position */
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - remove a key from the env
 * @key: the key that is to be removed
 * @data: the data structure of the program
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, data_of_program *data)
{
	int i, key_length = 0;

	/* validate the arg */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtains the length of the var requested */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{/* checks for coincidences */
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* remove the key if it exist */
			free(data->env[i]);

			/* move the other keys one position down */
			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			/* put the NULL value at the end of the new list */
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - prints the current environ
 * @data: data struct for the program
 * Return: nothing
 */
void print_environ(data_of_program *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
