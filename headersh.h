#ifndef HEADERSH
#define HEADERSH

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>


/*ERRORS*/

#define EXIT_IS_DIR (EISDIR + 1)
#define EXIT_NOT_ACCESS (EACCES + 1)
#define EXIT_NOT_EXIST (ENOENT + 1)

/**
* struct dlistint_s - doubly linked list
* @tokens: complete command list
* @buffer_in: output of the command when execute
* @next_deli: delimiter sign
* @status: error variable
* @prev: points to the previous node
* @next: points to the next node
*
* Description: doubly linked list node structure
* for Holberton project
*/
typedef struct dlistint_s
{
	char **tokens;
	char *buffer_in;
	char *next_deli;
	int status;
	struct dlistint_s *prev;
	struct dlistint_s *next;
} dlistint_t;

/**
* struct path_node - singly linked list
* @str: string - it a path directory
* @next: points to the next node
*
* Description: Store all the path directories
*/

typedef struct path_node
{
	char *str;
	struct path_node *next;
} path_node;

/**
* struct op - Struct op
*
* @op: The operator
* @f: The function associated
*/
typedef struct op
{
	char *op;
	int (*f)(char ***, char ***, char **, int *, char **, int *,
		dlistint_t **, char ***tok_com, dlistint_t *);
} op_t;

/*Utils*/
char *_strcat(char *dest, char *src);
int _strlen(char *st);
char *_itoa(int num, char *strnum);
int _strcmp(char *s1, char *s2);
int _strcmp_c(char *s1, char *s2);
int _strcmp_n(char *s1, char *s2, int n);
char *_strcpy(char *s1);

/*Main functions hsh*/
int simple_sh(char **av, char ***en);
int readsh(char **buffer, int *len);
void parsesh(char **buffer, int *len, char ***tokens, int *status);
int createandexesh(char ***, int *, char ***, char **, int *,
	dlistint_t **, char ***, dlistint_t *);

/*Utils main functions*/
char *_getenv(const char *variable_env, char **en);
path_node *_getpathdir(char *path, char **);
int add_path(char ***tokens, char **en);
void get_path(path_node **list_path, char **en);


/*Free all allocate variables*/
void free_list(path_node *list_path);
void free_all(char **buffer, char ***tokens, dlistint_t **head);

/*Print Error Built-in*/
void print_error_builtin(char *av, int cc, char **token, char *errmsg);
void open_errors(char *av, int cc, char *tok, int errmsg);
void print_error(char *av, int cc, char *tok, int errmsg);

/*Built-ins*/
int built_ins_sh(char ***tokens, char ***, char **, int *, char **,
	int *, dlistint_t **head, char ***tok_com, dlistint_t *);

int env(char ***en, char ***tokens, char **buffer, int *statuss, char **av,
	int *cc, dlistint_t **head, char ***tok_com, dlistint_t *cur_node);
int _setenv(char ***en, char ***tokens, char **buffer, int *, char **,
	int *, dlistint_t **head, char ***tok_com, dlistint_t *cur_node);
int _unsetenv(char ***en, char ***tokens, char **, int *, char **,
	int *, dlistint_t **head, char ***tok_com, dlistint_t *cur_node);

/*env utilities*/
char **envdup(char **env);
void freeenv(char **env);


/*Save mutiples commands*/
int save_mul_commands(dlistint_t **head, char ***tokens, int *status);
dlistint_t *add_dnodeint_end(dlistint_t **head);
void free_dlistint(dlistint_t *head);

/*Execute multiples commands*/
int exe_mul_commands(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head);

/*Utils for execute multiples commands*/
int realloc_buffer(char **buffer, char *str);
int create_pipe(int(*pipefd)[2]);
int read_command_output(int *pipefd, dlistint_t *cur_node);
int change_output_command(int *pipefd);


/*Files redirecctions*/
int set_normal_stdout(int stdout_copy);
int stdout_to_file(char *filename);
int stdout_to_end_file(char *filename);
int set_normal_stdin(int stdin_copy);
int stdout_to_stdin(int *pipefd);
int stdin_to_file(char *filename);

/*Utils operator execution*/
int redir_output_append(dlistint_t **head, char ***tok_com, int *status);
int redir_output(dlistint_t **head, char ***tok_com, int *status);
int or_condition(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head);
int and_condition(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head);
int exe_multi_commands(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head);
int out_redir_in(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head);
int redir_input(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head);
int redir_input_heredoc(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head);
#endif
