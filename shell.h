#ifndef _CUSTOM_SHELL_H_
#define _CUSTOM_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define CUSTOM_READ_BUFFER_SIZE 1024
#define CUSTOM_WRITE_BUFFER_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORMAL	0
#define CMD_OR	1
#define CMD_AND	2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE	".custom_shell_history"
#define HISTORY_MAX	4096

extern char **environ;

/**
 * struct custom_liststr - Structure for singly linked list node.
 * @num: The number associated with the node.
 * @str: The string stored in the node.
 * @next: Pointer to the next node.
 */
typedef struct custom_liststr
{
	int num;
	char *str;
	struct custom_liststr *next;
} list_t;

/**
 * struct custom_passinfo - Structure for passing arguments to functions.
 * This allows a uniform prototype for function pointer structs.
 * @arg: String generated from getline containing arguments.
 * @argv: Array of strings generated from arguments.
 * @path: String representing the path for the current command.
 * @argc: Argument count.
 * @line_count: Error count.
 * @err_num: Error code for exit() calls.
 * @linecount_flag: Flag to count this line of input.
 * @fname: The program's filename.
 * @env: Linked list, a local copy of the environment.
 * @history: Linked list for history.
 * @alias: Linked list for alias.
 * @environ: A pointer to the environment variables.
 * @env_changed: Flag to indicate if the environment was changed.
 * @status: Return status of the last executed command.
 * @cmd_buf: Pointer to the command buffer, used in chaining.
 * @cmd_buf_type: Type of command (normal, OR, AND, etc.).
 * @readfd: File descriptor for reading input.
 * @histcount: Line number count for history.
 */
typedef struct custom_passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
																	0, 0, 0}

/**
 * struct custom_builtin - Structure for defining a builtin.
 * command and its related function.
 * @type: The type of the builtin command.
 * @func: The function associated with the command.
 */
typedef struct custom_builtin
{
	char *type;
	int (*func)(info_t *);
} custom_builtin_table;

/* Function Declarations */

/* custom_shloop.c */
int hsh(info_t *, char **);
int custom_find_builtin(info_t *);
void custom_find_cmd(info_t *);
void custom_fork_cmd(info_t *);

/* custom_parser.c */
int custom_is_cmd(info_t *, char *);
char *custom_dup_chars(char *, int, int);
char *custom_find_path(info_t *, char *, char *);

/* custom_loophsh.c */
int custom_loophsh(char **);

/* custom_errors.c */
void _eputs(char *);
int _eputchar(char);
int custom_putfd(char c, int fd);
int custom_putsfd(char *str, int fd);

/* custom_string.c */
int custom_strlen(char *);
int custom_strcmp(char *, char *);
char *custom_starts_with(const char *, const char *);
char *custom_strcat(char *, char *);

/* custom_string1.c */
char *custom_strcpy(char *, char *);
char *custom_strdup(const char *);
void custom_puts(char *);
int custom_putchar(char);

/* custom_exits.c */
char *custom_strncpy(char *, char *, int);
char *custom_strncat(char *, char *, int);
char *custom_strchr(char *, char);

/* custom_tokenizer.c */
char **custom_strtow(char *, char *);
char **custom_strtow2(char *, char);

/* custom_realloc.c */
char *custom_memset(char *, char, unsigned int);
void custom_ffree(char **);
void *custom_realloc(void *, unsigned int, unsigned int);

/* custom_memory.c */
int custom_bfree(void **);

/* custom_atoi.c */
int custom_interactive(info_t *);
int custom_is_delim(char, char *);
int custom_isalpha(int);
int custom_atoi(char *);

/* custom_errors1.c */
int custom_erratoi(char *);
void custom_print_error(info_t *, char *);
int custom_print_d(int, int);
char *custom_convert_number(long int, int, int);
void custom_remove_comments(char *);

/* custom_builtin.c */
int custom_myexit(info_t *);
int custom_mycd(info_t *);
int custom_myhelp(info_t *);

/* custom_builtin1.c */
int custom_myhistory(info_t *);
int custom_myalias(info_t *);

/* custom_getline.c */
ssize_t custom_get_input(info_t *);
int custom_getline(info_t *, char **, size_t *);
void custom_sigintHandler(int);

/* custom_getinfo.c */
void custom_clear_info(info_t *);
void custom_set_info(info_t *, char **);
void custom_free_info(info_t *, int);

/* custom_environ.c */
char *custom_getenv(info_t *, const char *);
int custom_myenv(info_t *);
int custom_mysetenv(info_t *);
int custom_myunsetenv(info_t *);
int populate_env_list(info_t *);


/* custom_getenv.c */
char **custom_get_environ(info_t *);
int custom_unsetenv(info_t *, char *);
int custom_setenv(info_t *, char *, char *);

/* custom_history.c */
char *custom_get_history_file(info_t *info);
int custom_write_history(info_t *info);
int read_history(info_t *info);
int custom_build_history_list(info_t *info, char *buf, int linecount);
int custom_renumber_history(info_t *info);

/* custom_lists.c */
list_t *custom_add_node(list_t **, const char *, int);
list_t *custom_add_node_end(list_t **, const char *, int);
size_t custom_print_list_str(const list_t *);
int custom_delete_node_at_index(list_t **, unsigned int);
void custom_free_list(list_t **);

/* custom_lists1.c */
size_t custom_list_len(const list_t *);
char **custom_list_to_strings(list_t *);
size_t custom_print_list(const list_t *);
list_t *custom_node_starts_with(list_t *, char *, char);
ssize_t custom_get_node_index(list_t *, list_t *);

/* custom_vars.c */
int custom_is_chain(info_t *, char *, size_t *);
void custom_check_chain(info_t *, char *, size_t *, size_t, size_t);
int custom_replace_alias(info_t *);
int custom_replace_vars(info_t *);
int custom_replace_string(char **, char *);

#endif

