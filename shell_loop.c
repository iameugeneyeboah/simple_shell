#include "shell.h"

/**
 * hsh - Main shell loop.
 * @info: Pointer to the info_t struct.
 * @av: The argument vector from main().
 *
 * This function implements the main loop of the shell, where it reads input,
 * processes built-in commands, and executes external commands.
 *
 * Return: Returns 0 on success, 1 on error, or the appropriate exit code.
 */
int hsh(info_t *info, char **av)
{
	/* Implementation details */
}

/**
 * find_builtin - Finds and executes a built-in command.
 * @info: Pointer to the info_t struct.
 *
 * This function looks for the given cmd in the list of built-in commands,
 * executes the command if found, and returns the result.
 *
 * Return: Returns -1 if the built-in is not found,
 *         0 if the built-in executed successfully,
 *         1 if the built-in was found but not successful,
 *         2 if the built-in signals an exit().
 */
int find_builtin(info_t *info)
{
	/* Implementation details */
}

/**
 * find_cmd - Finds and executes a command in the PATH.
 * @info: Pointer to the info_t struct.
 *
 * This function searches for the provided command in the directories specified
 * in the PATH environment variable and executes the command if found.
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	/* Implementation details */
}

/**
 * fork_cmd - Forks a child process to execute a command.
 * @info: Pointer to the info_t struct.
 *
 * This fxn forks a child process to execute an external cmd using execve().
 * It waits for the child process to complete and updates the exit status.
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	/* Implementation details */
}
