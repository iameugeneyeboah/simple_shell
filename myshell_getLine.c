#include "myshell.h"

/**
 * sigintHandler - Blocks ctrl-C
 * @sig_num: The signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
        puts("\n");
        puts("$ ");
        putchar(MYSHELL_BUF_FLUSH);
}

/**
 * input_buf - Buffers chained commands
 * @info: Parameter struct
 * @buf: Address of buffer
 * @len: Address of len var
 * Return: Bytes read
 */
ssize_t input_buf(myshell_info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* If nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* Remove trailing newline */
				r--;
			}
			info->myshell_linecount_flag = 1;
			myshell_remove_comments(*buf);
			myshell_build_history_list(info, *buf, info->myshell_histcount++);
			/* if (_strchr(*buf, ';')) Is this a command chain? */
			{
				*len = r;
				info->myshell_cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - Gets a line minus the newline
 * @info: Parameter struct
 * Return: Bytes read
 */
ssize_t get_input(myshell_info_t *info)
{
	static char *buf; /* The ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->myshell_arg), *p;

	putchar(MYSHELL_BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* We have commands left in the chain buffer */
	{
		j = i; /* Initialize new iterator to current buf position */
		p = buf + i; /* Get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* Iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Increment past nulled ';'' */
		if (i >= len) /* Reached end of buffer? */
		{
			i = len = 0; /* Reset position and length */
			info->myshell_cmd_buf_type = MYSHELL_CMD_NORM;
		}

		*buf_p = p; /* Pass back pointer to current command position */
		return (strlen(p)); /* Return length of current command */
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - Reads a buffer
 * @info: Parameter struct
 * @buf: Buffer
 * @i: Size
 * Return: r
 */
ssize_t read_buf(myshell_info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->myshell_readfd, buf, MYSHELL_READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - Gets the next line of input from STDIN
 * @info: Parameter struct
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(myshell_info_t *info, char **ptr, size_t *length)
{
	static char buf[MYSHELL_READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = realloc(p, s + k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		strncat(new_p, buf + i, k - i);
	else
		strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
