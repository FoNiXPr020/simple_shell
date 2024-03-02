#ifndef MAIN_H
#define MAIN_H

#define PROMPT "#csisfun$ "

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

extern char **environ;

/**
 * struct data - Structure to hold main shell data.
 * @vr_arry: Array of tokens to pass for execve
 * @cmd: The user input, representing the command line
 * @shell_name: The name of the shell program
 * @last_exit_status: The exit status of the last command executed
 * @flag_setenv: Indicates whether the user
 * executed the setenv command (useful for memory management)
 */
typedef struct data
{
	char **vr_arry;
	char *cmd;
	const char *shell_name;
	int last_exit_status;
	int flag_setenv;
} data;

/**
 * struct builtin - Structure to hold information about a built-in command.
 * @cmd: Built-in command name
 * @f: Pointer to the function handling the built-in command
 */
typedef struct builtin
{
	const char *cmd;
	void (*f)(data *d);
} builtin;

/* functions_builtin.c && functions2_builtin.c */
int builtin_exec(data *d);
void exit_builtin(data *d);
void env_builtin(data *d);
void setenv_builtin(data *d);
void unsetenv_builtin(data *d);
void cd_builtin(data *d);

/* functions.c */
void _printf(const char *str);
void release_pointers(char **array);
void parse_string(data *d, const char *delim);
void initialize_data(data *d, const char *shell_name);
void retrieve_command(data *d);

/* functions2.c */
void _print_error(const char *str1, const char *str2);
void _trim_string(char *str);
void *_realloc(void *ptr, unsigned int new_size);

/* functions_exec.c */
void initiate_process(data *d);
void handle_interrupt(int sig);
void execute_command(data *d);

/* functions_path.c */
char *_fetchenv(char *name);
int _search_executable(data *d);
int _set_env(data *d, char *name, char *value);

/* functions_utils.c */
unsigned int _string_len(char *str);
int _string_compare(const char *s1, const char *s2);
int _string_com_limit(const char *s1, const char *s2, int n);
char *_string_copy(char *dest, const char *src);
char *_string_concat(char *dest, const char *src);

/* functions_utils2.c */
char *_string_dupli(const char *str);
int _is_number(const char *status);
int _is_digit(int c);

/* functions_getline.c */
#define READ_BUF_SIZE 1024
ssize_t _custom_getline(char **lineptr, size_t *n, FILE *stream);

/* END OF MAIN */
#endif

