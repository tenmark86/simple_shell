#include "headersh.h"

/**
* redir_output_append - choose the correct option to exe a commmand
* @head: all commands in a line
* @tok_com: ONE command of a line
* @status: status
* Return: the process status
*/
int redir_output_append(dlistint_t **head, char ***tok_com, int *status)
{
	int stdout_copy = dup(1), result = 0;

	result = stdout_to_end_file(**tok_com);

	if (result == EXIT_IS_DIR || result == EXIT_NOT_ACCESS)
	{
		*status = 2;
		return (result);
	}
	if ((*head)->buffer_in)
	{
		printf("%s", (*head)->buffer_in);
		fflush(stdout);
	}
	set_normal_stdout(stdout_copy);
	return (0);
}

/**
* redir_output - choose the correct option to exe a commmand
* @head: all commands in a line
* @tok_com: ONE command of a line
* @status: status
* Return: the process status
*/
int redir_output(dlistint_t **head, char ***tok_com, int *status)
{
	int stdout_copy = dup(1), result = 0;

	result = stdout_to_file(**tok_com);

	if (result == EXIT_IS_DIR || result == EXIT_NOT_ACCESS)
	{
		*status = 2;
		return (result);
	}
	if ((*head)->buffer_in)
	{
		printf("%s", (*head)->buffer_in);
		fflush(stdout);
	}
	set_normal_stdout(stdout_copy);
	return (0);
}

/**
* exe_one_command - choose the correct option to exe a commmand
* @tokens: strings from stdin
* @cc: is the counter of commans executes by user
* @en: list containing the end parameter for execve syscall
* @av: list containing the arguments given by user
* @status: previous loop status
* @head: all commands in a line
* @tok_com: ONE command of a line
* @copy_head: current node command
* Return: the process status
*/
int or_condition(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head)
{
	int flag_terminator = 0;

	if (copy_head->prev->status)
		createandexesh(tokens, cc, en, av, status, head, tok_com,
			copy_head);
	else
		flag_terminator = 1;
	return (flag_terminator);
}

/**
* exe_one_command - choose the correct option to exe a commmand
* @tokens: strings from stdin
* @cc: is the counter of commans executes by user
* @en: list containing the end parameter for execve syscall
* @av: list containing the arguments given by user
* @status: previous loop status
* @head: all commands in a line
* @tok_com: ONE command of a line
* @copy_head: current node command
* Return: the process status
*/
int and_condition(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head)
{
	int flag_terminator = 0;

	if (!copy_head->prev->status)
		createandexesh(tokens, cc, en, av, status, head, tok_com,
			copy_head);
	else
		flag_terminator = 1;
	return (flag_terminator);
}

/**
* exe_one_command - choose the correct option to exe a commmand
* @tokens: strings from stdin
* @cc: is the counter of commans executes by user
* @en: list containing the end parameter for execve syscall
* @av: list containing the arguments given by user
* @status: previous loop status
* @head: all commands in a line
* @tok_com: ONE command of a line
* @copy_head: current node command
* Return: the process status
*/
int exe_multi_commands(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head)
{
	createandexesh(tokens, cc, en, av, status, head, tok_com, copy_head);
	return (0);
}
