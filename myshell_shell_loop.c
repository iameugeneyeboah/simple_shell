#include "myshell.h"

/**
 * myshell_main_loop - Main shell loop
 * @info: Pointer to the shell info struct
 * @av: Argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int myshell_main_loop(myshell_info_t *info, char **av)
{
	ssize_t read_status = 0;
	int builtin_ret = 0;

	while (read_status != -1 && builtin_ret != -2)
	{
		myshell_clear_info(info);
		if (myshell_interactive(info))
			myshell_puts("$ ");
		myshell_eputchar(MYSHELL_BUF_FLUSH);
		read_status = myshell_get_input(info);
		if (read_status != -1)
		{
			myshell_set_info(info, av);
			builtin_ret = myshell_find_builtin(info);
			if (builtin_ret == -1)
				myshell_find_cmd(info);
		}
		else if (myshell_interactive(info))
			myshell_putchar('\n');
		myshell_free_info(info, 0);
	}
	myshell_write_history(info);
	myshell_free_info(info, 1);
	if (!myshell_interactive(info) && info->myshell_status)
		exit(info->myshell_status);
	if (builtin_ret == -2)
	{
		if (info->myshell_err_num == -1)
			exit(info->myshell_status);
		exit(info->myshell_err_num);
	}
	return (builtin_ret);
}

/**
 * myshell_find_builtin - Find a builtin command
 * @info: Pointer to the shell info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         2 if builtin signals exit()
 */
int myshell_find_builtin(myshell_info_t *info)
{
	int i, builtin_ret = -1;
	myshell_builtin_table builtintbl[] = {
		{"exit", myshell_myexit},
		{"env", myshell_myenv},
		{"help", myshell_myhelp},
		{"history", myshell_myhistory},
		{"setenv", myshell_mysetenv},
		{"unsetenv", myshell_myunsetenv},
		{"cd", myshell_mycd},
		{"alias", myshell_myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].myshell_type; i++)
		if (myshell_strcmp(info->myshell_argv[0], builtintbl[i].myshell_type) == 0)
		{
			info->myshell_line_count++;
			builtin_ret = builtintbl[i].myshell_func(info);
			break;
		}
	return (builtin_ret);
}

/**
 * myshell_find_cmd - Find a command in PATH
 * @info: Pointer to the shell info struct
 *
 * Return: void
 */
void myshell_find_cmd(myshell_info_t *info)
{
	char *path = NULL;
	int i, arg_len;

	info->myshell_path = info->myshell_argv[0];
	if (info->myshell_linecount_flag == 1)
	{
		info->myshell_line_count++;
		info->myshell_linecount_flag = 0;
	}
	for (i = 0, arg_len = 0; info->myshell_arg[i]; i++)
		if (!myshell_is_delim(info->myshell_arg[i], " \t\n"))
			arg_len++;
	if (!arg_len)
		return;

	path = myshell_find_path(info, myshell_getenv(info, "PATH="), info->myshell_argv[0]);
	if (path)
	{
		info->myshell_path = path;
		myshell_fork_cmd(info);
	}
	else
	{
		if ((myshell_interactive(info) || myshell_getenv(info, "PATH=")
				|| info->myshell_argv[0][0] == '/') && myshell_is_cmd(info, info->myshell_argv[0]))
			myshell_fork_cmd(info);
		else if (*(info->myshell_arg) != '\n')
		{
			info->myshell_status = 127;
			myshell_print_error(info, "not found\n");
		}
	}
}

/**
 * myshell_fork_cmd - Forks a child process to run the command
 * @info: Pointer to the shell info struct
 *
 * Return: void
 */
void myshell_fork_cmd(myshell_info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: Implement error handling function */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->myshell_path, info->myshell_argv, myshell_get_environ(info)) == -1)
		{
			myshell_free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: Implement error handling function */
	}
	else
	{
		wait(&(info->myshell_status));
		if (WIFEXITED(info->myshell_status))
		{
			info->myshell_status = WEXITSTATUS(info->myshell_status);
			if (info->myshell_status == 126)
				myshell_print_error(info, "Permission denied\n");
		}
	}
}
