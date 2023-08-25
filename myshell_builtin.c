#include "myshell.h"

/**
 * myshell_exit - Exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int myshell_exit(info_t *info)
{
	int exit_check;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_check = myshell_erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			myshell_print_error(info, "Illegal number: ");
			myshell_eputs(info->argv[1]);
			myshell_eputchar('\n');
			return (1);
		}
		info->err_num = myshell_erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * myshell_cd - Changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int myshell_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		myshell_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = myshell_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = myshell_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (myshell_strcmp(info->argv[1], "-") == 0)
	{
		if (!myshell_getenv(info, "OLDPWD="))
		{
			myshell_puts(s);
			myshell_putchar('\n');
			return (1);
		}
		myshell_puts(myshell_getenv(info, "OLDPWD=")), myshell_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = myshell_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		myshell_print_error(info, "can't cd to ");
		myshell_eputs(info->argv[1]), myshell_eputchar('\n');
	}
	else
	{
		myshell_setenv(info, "OLDPWD", myshell_getenv(info, "PWD="));
		myshell_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * myshell_help - Prints help information
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int myshell_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	myshell_puts("help call works. Function not yet implemented \n");
	if (0)
		myshell_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
