#include "myshell.h"

/**
 * myshell_strlen - Returns the length of a string
 * @str: The string whose length to check
 *
 * Return: Integer length of string
 */
int myshell_strlen(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;
	return (length);
}

/**
 * myshell_strcmp - Performs lexicographic comparison of two strings
 * @str1: The first string
 * @str2: The second string
 *
 * Return: Negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int myshell_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * myshell_starts_with - Checks if a string starts with a given substring
 * @str: The string to search
 * @prefix: The substring to find
 *
 * Return: Address of the next character after the prefix in str or NULL
 */
char *myshell_starts_with(const char *str, const char *prefix)
{
	while (*prefix)
		if (*prefix++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * myshell_strcat - Concatenates two strings
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Return: Pointer to the destination buffer
 */
char *myshell_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (result);
}
