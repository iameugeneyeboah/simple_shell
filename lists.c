#include "shell.h"

/**
 * add_node - Creates a new node and adds it to the beginning of the list.
 * @head: Address of the pointer to the head node.
 * @str: String to be stored in the new node.
 * @num: Index used for history.
 *
 * Return: Pointer to the newly created node, or NULL on failure.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * add_node_end - Creates a new node and adds it to the end of the list.
 * @head: Address of the pointer to the head node.
 * @str: String to be stored in the new node.
 * @num: Index used for history.
 *
 * Return: Pointer to the newly created node, or NULL on failure.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * print_list_str - Prints only the 'str' element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Number of nodes in the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * delete_node_at_index - Deletes a node at the specified index in the list.
 * @head: Address of the pointer to the first node.
 * @index: Index of the node to be deleted.
 *
 * Return: 1 if successful, 0 otherwise.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int count = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *head;
	while (node)
	{
		if (count == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		count++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_list - Frees all nodes in the linked list.
 * @head_ptr: Address of the pointer to the head node.
 *
 * Return: void.
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	node = head;

	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}
