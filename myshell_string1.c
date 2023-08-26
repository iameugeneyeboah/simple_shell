#include "myshell.h"

/**
 * myshell_strcpy - Copies a string
 * @destination: The destination
 * @source: The source
 *
 * Return: Pointer to destination
 */
char *myshell_strcpy(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == NULL)
		return (destination);
	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = '\0';
	return (destination);
}

/**
 * myshell_strdup - Duplicates a string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *myshell_strdup(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--str;
	return (result);
}

/**
 * myshell_puts - Prints an input string
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void myshell_puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		myshell_putchar(str[index]);
		index++;
	}
}

/**
 * myshell_putchar - Writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int myshell_putchar(char c)
{
	static int index;
	static char buffer[MYSHELL_WRITE_BUF_SIZE];

	if (c == MYSHELL_BUF_FLUSH || index >= MYSHELL_WRITE_BUF_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}
	if (c != MYSHELL_BUF_FLUSH)
		buffer[index++] = c;
	return (1);
}
