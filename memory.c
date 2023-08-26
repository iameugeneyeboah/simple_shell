#include "shell.h"

/**
 * free_and_null - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to be freed.
 *
 * This fxn frees memory allocated for the pointer 'ptr' and sets the pointer
 * to NULL, preventing further access to the memory it pointed to. If 'ptr' is
 * NULL or points to NULL, the function has no effect.
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

