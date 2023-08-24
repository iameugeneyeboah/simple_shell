#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h> /* printf*/
#include <string.h> /* strtok*/
#include <fcntl.h> /* open files*/
#include <sys/wait.h> /* wait */
#include <unistd.h> /* fork */
#include <sys/types.h> /* type pid */
#include <sys/stat.h> /* stat function */
#include <signal.h> /* signal management */
#include <errno.h> /* errno and perror */


/**
 * struct info- structure for the program's data
 * @program_name: name of the executable file
 * @tokens: pointer to array of tokenized input                             
 * @env: copy of the env
 * @input_line: pointer to the input read of _getline
 * @command_name: pointer to the first command
 * @exec_counter: number of excecuted commands
 * @alias_list: array of pointers with aliases.
 * @file_descriptor: file descriptor to the input of commands
 */
typedef struct info
{
        int exec_counter;
        int file_descriptor;
        char *command_name;
	char *input_line;
	char *program_name;
	char **env;
	char **alias_list;
	char **token;
} data_of_program;


/**
 * struct builtins - builtins structure
 * @builtin: builtin's name
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;


/*========  _getline.c  ========*/

/* Reads one line of the stdit*/
int _getline(data_of_program *data);

/* splits each line for the logical operators if they exist */
int check_logic_ops(char *array_commands[], int i, char array_operators[]);


/*========  shell.c  ========*/

/* Inicialize the struct with the information of the program */
void inicialize_data(data_of_program *data, int arc, char *argv[], char **env);

/* Prints the prompt in a new line */
void handle_ctrl_c(int opr UNUSED);

/* Makes the infinite loop that shows the prompt*/
void sisifo(char *prompt, data_of_program *data);


/*======== str_tok.c ========*/

/* Separates the string in tokens using a designed delimiter */
void tokenize(data_of_program *data);

/* Creates a pointer to a part of a string */
char *_strtok(char *line, char *delim);


/*======== execute.c ========*/

/* Executes a command with its entire path */
int execute(data_of_program *data);


/*======== expansions.c ========*/

/* expands the aliases */
void expand_alias(data_of_program *data);

/* expands the var */
void expand_variables(data_of_program *data);

/* appends the string to the end of the buffer*/
int buffer_add(char *buffer, char *str_to_add);


/*======== find_in_path.c ========*/

/* Creates an array of the path directories */
char **tokenize_path(data_of_program *data);

/* Searches for a program in the path */
int find_program(data_of_program *data);


/*======== builtins_list.c ========*/

/* Executes if matches a builtin */
int builtins_list(data_of_program *data);


/*======== builtins_more.c ========*/

/* closes the shell */
int builtin_exit(data_of_program *data);

/* changes the cd */
int builtin_cd(data_of_program *data);

/* sets the work directory */
int set_work_directory(data_of_program *data, char *new_dir);

/* shows help */
int builtin_help(data_of_program *data);

/* sets, unsets and shows the alias */
int builtin_alias(data_of_program *data);


/*======== helpers_free.c ========*/

/* Frees the fields needed for each loop */
void free_recurrent_data(data_of_program *data);

/* Frees the memory for directories */
void free_array_of_pointers(char **directories);

/* Free all data fields */
void free_all_data(data_of_program *data);


/*======== builtins_env.c ========*/

/* deletes var of env */
int builtin_unset_env(data_of_program *data);

/* Shows the environment where the shell runs */
int builtin_env(data_of_program *data);

/* creates and or overrides a var of env */
int builtin_set_env(data_of_program *data);


/*======== env_management.c ========*/

/* Removes a key from the env */
int env_remove_key(char *key, data_of_program *data);

/* Gets the value of an environ's var */
char *env_get_key(char *name, data_of_program *data);

/* prints the current env */
void print_environ(data_of_program *data);

/* Overwrites the value of the environ's var */
int env_set_key(char *key, char *value, data_of_program *data);


/*======== helpers_string.c ========*/

/* Counts the number of char of a string */
int str_length(char *string);

/* Compares two strings */
int str_compare(char *string1, char *string2, int number);

/* Duplicates a string */
char *str_duplicate(char *string);

/* Reverse a string */
void str_reverse(char *string);

/* Concatenates two strings */
char *str_concat(char *string1, char *string2);


/*======== alias_management.c ========*/

/* prints all the list of alias */
int print_alias(data_of_program *data, char *alias);

/* sets the name of the alias */
int set_alias(char *alias_string, data_of_program *data);

/* gets the name of the alias */
char *get_alias(data_of_program *data, char *alias);


/*======== helpers_print.c ========*/

/* Prints a string in the stdout */
int _print(char *string);

/* Prints a string in the standard error */
int _print_error(int errorcode, data_of_program *data);

/* Prints a string in the standard error */
int _printe(char *string);


/*======== helpers_numbers.c ========*/

/* converts a string to a num */
int _atoi(char *s);

/* counts the coincidences of char in string */
int count_characters(char *string, char *character);

/* casts from int to string */
void long_to_string(long number, char *string, int base);


#endif
