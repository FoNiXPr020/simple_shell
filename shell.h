#ifndef _SHELL_H_
#define _SHELL_H_

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

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - Singly linked list node.
 * @num: The number field.
 * @str: A string.
 * @next: Points to the next node.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Contains pseudo-arguments to pass into a function,
 * allowing uniform prototype for function pointer struct.
 * @arg: A string generated from getline containing arguments.
 * @argv: An array of strings generated from arg.
 * @path: A string path for the current command.
 * @argc: The argument count.
 * @line_count: The error count.
 * @err_num: The error code for exit().
 * @linecount_flag: If on count this line of input.
 * @fname: The program filename.
 * @env: Linked list local copy of environ.
 * @environ: Custom modified copy of environ from LL env.
 * @history: The history node.
 * @alias: The alias node.
 * @env_changed: On if environ was changed.
 * @status: The return status of the last exec'd command.
 * @cmd_buf: Address of pointer to cmd_buf, on if chaining.
 * @cmd_buf_type: CMD_type ||, &&, ;.
 * @readfd: The fd from which to read line input.
 * @histcount: The history line number count.
 */
typedef struct passinfo
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
 * struct builtin - Contains a builtin string and related function.
 * @type: The builtin command flag.
 * @func: The function pointer.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int run_shell(info_t *, char **);
int search_builtin(info_t *);
void search_command(info_t *);
void fork_execute(info_t *);

int check_command(info_t *, char *);
char *duplicate_characters(char *, int, int);
char *search_in_path(info_t *, char *, char *);

void _eputs(char *);
int _eput_char(char);
int _put_fd(char c, int fd);
int _puts_fd(char *str, int fd);

int _string_length(char *);
int _string_compare(char *, char *);
char *check_prefix(const char *, const char *);
char *_string_concat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_copy_string_n(char *, char *, int);
char *_cat_strings_n(char *, char *, int);
char *_find_character(char *, char);

char **split_string(char *, char *);

char *_fill_memory(char *, char, unsigned int);
void free_string_array(char **);
void *_reallocate(void *, unsigned int, unsigned int);

int free_and_nullify(void **);

int inter_active(info_t *);
int is_delimiter(char, char *);
int is_alphabetic(int);
int _atoi_conv(char *);

int _convert_to_integer(char *);
void display_error(info_t *, char *);
int print_decimal(int, int);
char *number_conversion(long int, int, int);
void eliminate_comments(char *);

int _exit_shell(info_t *);
int _cd_directory(info_t *);
int _display_help(info_t *);

int _display_history(info_t *);
int _handle_shell_alias(info_t *);

ssize_t get_input_newline(info_t *);
int _retrieve_line(info_t *, char **, size_t *);
void handle_SIGINT(int);

void initialize_info(info_t *);
void initialize_info_arg(info_t *, char **);
void release_info(info_t *, int);

char *_get_environ(info_t *, const char *);
int _environ_print(info_t *);
int _set_environ(info_t *);
int _unset_environ(info_t *);
int initialize_environ(info_t *);

char **copy_environment(info_t *);
int _remove_env_var(info_t *, char *);
int _set_env_var(info_t *, char *, char *);

char *retrieve_history_file(info_t *info);
int create_or_append_history(info_t *info);
int read_history_from_file(info_t *info);
int add_entry_to_history_list(info_t *info, char *buf, int linecount);
int renumber_history_list(info_t *info);

list_t *prepend_node(list_t **, const char *, int);
list_t *append_node(list_t **, const char *, int);
size_t print_string_list(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void deallocate_list(list_t **);

size_t determine_list_length(const list_t *);
char **convert_list_to_strings(list_t *);
size_t display_list(const list_t *);
list_t *find_node_with_prefix(list_t *, char *, char);
ssize_t obtain_node_index(list_t *, list_t *);

int is_chain_delimiter(info_t *, char *, size_t *);
void check_continuation(info_t *, char *, size_t *, size_t, size_t);
int substitute_aliases(info_t *);
int substitute_variables(info_t *);
int substitute_string(char **, char *);

/* END OF SHELL*/
#endif

