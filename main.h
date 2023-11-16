#ifndef MAIN_H
#define MAIN_H

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

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct strlist - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct strlist
{
	int num;
	char *str;
	struct strlist *next;
} env_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@argc: argument count
 *@av:  array of strings
 *@arg: getline string
 *@fname: program name
 *@path: command path string
 *@env: list environ
 *@environ: modified environ
 *@line_count: error count
 *@err_num: exit()s error code
 *@linecount_flag: count
 *@history: node history
 *@alias: different name
 *@env_changed: boolean env changed
 *@status: status
 *@cmd_buf: address chain
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: file descriptor
 *@histcount: history
 */
typedef struct passinfo
{
	int argc;
	char **av;
	char *arg;
	char *fname;
	char *path;
	env_t *env;
	char **environ;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	env_t *history;
	env_t *alias;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} global_t;

#define INIT \
{0, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(global_t *);
} inbuilt_t;

void _find(global_t *);
int find_builtin(global_t *);
int simple_shell(global_t *, char **);
void _fork(global_t *);


char *dup_chars(char *, int, int);
int _is_cmd(global_t *, char *);
char *find_path(global_t *, char *, char *);
void _eputs(char *);
char *_strcat(char *, char *);
int _loop(char **);
int _putsfd(char *str, int fd);
int _eputchar(char);
int _putfd(char c, int fd);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
int _strlen(char *);
char *_strcpy(char *, char *);
char *_strncpy(char *dest, const char *src, size_t n);

char *_strdup(const char *);
int _putchar(char);
char *_strncat(char *, char *, int);
void _puts(char *);
char *_strchr(char *, char);

char **_strtok(char *, char *);
char **_strtok2(char *, char);

char *_memset(char *, char, unsigned int);
void freef(char **);
void *_realloc(void *, unsigned int, unsigned int);
int is_separator(char, char *);

int _erratoi(char *);

int freeb(void **);
char *convert_num(long int, int, int);

int is_terminal(global_t *);
int _isalpha(int);
int _atoi(char *);
void print_error(global_t *, char *);
int print_d(int, int);
void comments_rm(char *);

int _mexit(global_t *);
int _cd(global_t *);
int _myhelp(global_t *);

int _myhistory(global_t *);
int _myalias(global_t *);

ssize_t get_input(global_t *);
int _getline(global_t *, char **, size_t *);
void sigintHandler(int);

void clear_global(global_t *);
void set_global(global_t *, char **);
void free_global(global_t *, int);

char *_getenv(global_t *, const char *);
int _myenv(global_t *);
int _mysetenv(global_t *);
int _myunsetenv(global_t *);
int populate_env_list(global_t *);

/* _getenv.c */
char **retrieve_environ(global_t *);
int _unsetenv(global_t *, char *);
int _setenv(global_t *, char *, char *);

/* _history.c */
char *get_history_file(global_t *global);
int write_history(global_t *global);
int check_history(global_t *global);
int build_history_list(global_t *global, char *buf, int linecount);
int renumber_history(global_t *global);

/* _lists.c */
env_t *add_node(env_t **, const char *, int);
env_t *add_node_end(env_t **, const char *, int);
size_t print_list_str(const env_t *);
int delete_node_at_index(env_t **, unsigned int);
void free_list(env_t **);

/* _lists1.c */
size_t list_len(const env_t *);
char **env_to_strings(env_t *);
size_t print_list(const env_t *);
env_t *node_starts_with(env_t *, char *, char);
ssize_t get_node_index(env_t *, env_t *);

/* _vars.c */
int is_chain(global_t *, char *, size_t *);
void check_chain(global_t *, char *, size_t *, size_t, size_t);
int swap_alias(global_t *);
int swap_vars(global_t *);
int replace_string(char **, char *);

int unset_alias(global_t *global, char *str);

#endif
