/* myshell_shell.h */
#ifndef MYSHELL_SHELL_H
#define MYSHELL_SHELL_H

#include <history.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

/* Read and write buffer sizes */
#define MYSHELL_READ_BUF_SIZE 1024
#define MYSHELL_WRITE_BUF_SIZE 1024
#define MYSHELL_BUF_FLUSH -1

/* Command chaining modes */
#define MYSHELL_CMD_NORM 0
#define MYSHELL_CMD_OR 1
#define MYSHELL_CMD_AND 2
#define MYSHELL_CMD_CHAIN 3

/* Convert number flags */
#define MYSHELL_CONVERT_LOWERCASE 1
#define MYSHELL_CONVERT_UNSIGNED 2

/* System getline usage flags */
#define MYSHELL_USE_GETLINE 0
#define MYSHELL_USE_STRTOK 0

#define MYSHELL_HISTORY_FILE ".myshell_history"
#define MYSHELL_HISTORY_MAX 4096

extern char **myshell_environ;


/**
 * struct myshell_list - singly linked list for myshell
 * @num: the number associated with the node
 * @str: a string stored in the node
 * @next: points to the next node in the list
 */
typedef struct myshell_list
{
    int num;
    char *str;
    struct myshell_list *next;
} myshell_list_t;


/**
 * struct MyShellInfo - Container for pseudo-arguments to be passed into functions,
 * allowing for a uniform prototype in function pointers.
 * @arg: A string generated from getline containing command arguments.
 * @argv: An array of strings generated from the command arguments.
 * @path: The string representing the path to the current command.
 * @argc: The count of command arguments.
 * @line_count: The count of lines encountered as errors.
 * @err_num: The error code used in exit() calls.
 * @linecount_flag: If enabled, counts this line of input.
 * @fname: The name of the program file.
 * @env: Linked list containing a local copy of the environment variables.
 * @environ: Custom modified copy of environment variables from LL env.
 * @history: The history node.
 * @alias: The alias node.
 * @env_changed: Indicates whether the environment variables were changed.
 * @status: The return status of the last executed command.
 * @cmd_buf: Address of a pointer to cmd_buf; enabled if command chaining is used.
 * @cmd_buf_type: Type of command chaining: CMD_type ||, &&, or ;.
 * @readfd: The file descriptor used to read line input.
 * @histcount: The history line number count.
 */
typedef struct MyShellInfo {
    char *myshell_arg;
    char **myshell_argv;
    char *myshell_path;
    int myshell_argc;
    unsigned int myshell_line_count;
    int myshell_err_num;
    int myshell_linecount_flag;
    char *myshell_fname;
    myshell_list_t *myshell_env;
    myshell_list_t *myshell_history;
    myshell_list_t *myshell_alias;
    char **myshell_environ;
    int myshell_env_changed;
    int myshell_status;
    char **myshell_cmd_buf;
    int myshell_cmd_buf_type;
    int myshell_readfd;
    int myshell_histcount;
} myshell_info_t;

#define MYSHELL_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

/* Builtin command structure */
typedef struct MyShellBuiltin {
    char *myshell_type;
    int (*myshell_func)(myshell_info_t *);
} myshell_builtin_table;

/* The main function of the custom shell */
int myshell(myshell_info_t *, char **);

/* Identifies if a command is a built-in function */
int myshell_find_builtin(myshell_info_t *);

/* Finds a specific command in the shell */
void myshell_find_cmd(myshell_info_t *);

/* Forks and executes a command in the shell */
void myshell_fork_cmd(myshell_info_t *);

/* myshell_shloop.c */
int myshell_shloop(myshell_info_t *, char **);
int myshell_find_builtin(myshell_info_t *);
void myshell_find_cmd(myshell_info_t *);
void myshell_fork_cmd(myshell_info_t *);

/* myshell_parser.c */
int myshell_is_cmd(myshell_info_t *, char *);
char *myshell_dup_chars(char *, int, int);
char *myshell_find_path(myshell_info_t *, char *, char *);

/* myshell_errors.c */
void myshell_eputs(char *);
int myshell_eputchar(char);
int myshell_putfd(char c, int fd);
int myshell_putsfd(char *str, int fd);

/* myshell_string.c */
int myshell_strlen(char *);
int myshell_strcmp(char *, char *);
char *myshell_starts_with(const char *, const char *);
char *myshell_strcat(char *, char *);

/* myshell_string1.c */
char *myshell_strcpy(char *, char *);
char *myshell_strdup(const char *);
void myshell_puts(char *);
int myshell_putchar(char);

/* myshell_exits.c */
char *myshell_strncpy(char *, char *, int);
char *myshell_strncat(char *, char *, int);
char *myshell_strchr(char *, char);

/* myshell_tokenizer.c */
char **myshell_strtow(char *, char *);
char **myshell_strtow2(char *, char);

/* myshell_realloc.c */
char *myshell_memset(char *, char, unsigned int);
void myshell_ffree(char **);
void *myshell_realloc(void *, unsigned int, unsigned int);

/* myshell_memory.c */
int myshell_bfree(void **);

/* myshell_atoi.c */
int myshell_interactive(myshell_info_t *);
int myshell_is_delim(char, char *);
int myshell_is_alpha(int);
int myshell_atoi(char *);

/* myshell_errors1.c */
int myshell_erratoi(char *);
void myshell_print_error(myshell_info_t *, char *);
int myshell_print_d(int, int);
char *myshell_convert_number(long int, int, int);
void myshell_remove_comments(char *);

/* myshell_builtin.c */
int myshell_myexit(myshell_info_t *);
int myshell_mycd(myshell_info_t *);
int myshell_myhelp(myshell_info_t *);

/* myshell_builtin1.c */
int myshell_myhistory(myshell_info_t *);
int myshell_myalias(myshell_info_t *);
int myshell_myenv(myshell_info_t *);

/* myshell_getLine.c */
ssize_t myshell_get_input(myshell_info_t *);
int myshell_getline(myshell_info_t *, char **, size_t *);
void myshell_sigintHandler(int);

/* myshell_getinfo.c */
void myshell_clear_info(myshell_info_t *);
void myshell_set_info(myshell_info_t *, char **);
void myshell_free_info(myshell_info_t *, int);

/* myshell_environ.c */
char *myshell_getenv(myshell_info_t *, const char *);
int myshell_myenv(myshell_info_t *);
int myshell_mysetenv(myshell_info_t *);
int myshell_myunsetenv(myshell_info_t *);
int myshell_populate_env_list(myshell_info_t *);

/* myshell_getenv.c */
char **myshell_get_environ(myshell_info_t *);
int myshell_unsetenv(myshell_info_t *, char *);
int myshell_setenv(myshell_info_t *, char *, char *);

/* myshell_history.c */
char *myshell_get_history_file(myshell_info_t *info);
int myshell_write_history(myshell_info_t *info);
int myshell_read_history(myshell_info_t *info);
int myshell_build_history_list(myshell_info_t *info, char *buf, int linecount);
int myshell_renumber_history(myshell_info_t *info);

/* myshell_lists.c */
myshell_list_t *myshell_add_node(myshell_list_t **, const char *, int);
myshell_list_t *myshell_add_node_end(myshell_list_t **, const char *, int);
size_t myshell_print_list_str(const myshell_list_t *);
int myshell_delete_node_at_index(myshell_list_t **, unsigned int);
void myshell_free_list(myshell_list_t **);

/* myshell_lists1.c */
size_t myshell_list_len(const myshell_list_t *);
char **myshell_list_to_strings(myshell_list_t *);
size_t myshell_print_list(const myshell_list_t *);
myshell_list_t *myshell_node_starts_with(myshell_list_t *, char *, char);
ssize_t myshell_get_node_index(myshell_list_t *, myshell_list_t *);

/* myshell_vars.c */
int myshell_is_chain(myshell_info_t *, char *, size_t *);
void myshell_check_chain(myshell_info_t *, char *, size_t *, size_t, size_t);
int myshell_replace_alias(myshell_info_t *);
int myshell_replace_vars(myshell_info_t *);
int myshell_replace_string(char **, char *);

#endif
