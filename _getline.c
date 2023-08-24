#include "shell.h"

/**
* _getline - read only one line from the prompt.
* @data: struct for the data of this program
*
* Return: reading counting bytes.
*/
int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	/* check if it does not exist more commands in the array */
	/* and checks the logical operators */
	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		/* if the memory allocated in the array exists then free it */
		for (i = 0; array_commands[i]; i++)
		{
			free(array_commands[i]);
			array_commands[i] = NULL;
		}

		/* reads from the file descriptor integer to buffer */
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* this splits lines for \n or ; */
		i = 0;
		do {
			array_commands[i] = str_duplicate(_strtok(i ? NULL : buff, "\n;"));
			/* this checks and splits for && and || operators */
			i = check_logic_ops(array_commands, i, array_operators);
		} while (array_commands[i++]);
	}

	/* obtains the next command (command 0) and removes it for the array */
	data->input_line = array_commands[0];
	for (i = 0; array_commands[i]; i++)
	{
		array_commands[i] = array_commands[i + 1];
		array_operators[i] = array_operators[i + 1];
	}

	return (str_length(data->input_line));
}


/**
* check_logic_ops - checks and splits for && and || operators
* @array_commands: this is the array of the commands.
* @i: the index in the array_commands to be checked
* @array_operators: the array of the logical operators for each previous command
*
* Return: the index of the last command in the array_commands.
*/
int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *temp = NULL;
	int j;

	/* checks for the & char in the command line */
	for (j = 0; array_commands[i] != NULL  && array_commands[i][j]; j++)
	{
		if (array_commands[i][j] == '&' && array_commands[i][j + 1] == '&')
		{
			/* splits line when chars && is found */
			temp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + j + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			j = 0;
		}
		if (array_commands[i][j] == '|' && array_commands[i][j + 1] == '|')
		{
			/* splits line when chars || is found */
			temp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(temp + j + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}
