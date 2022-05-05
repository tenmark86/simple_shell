#include "headersh.h"

/**
* sign_com_pos - get the index of the delimiter in the array
* @next_deli: next delimiter
* Return: return the index of the delimiter in the array
*/
int sign_com_pos(char *next_deli)
{
	char *all_f_gene[] = {">>", ">", "<<", "<", "||", "|", ";", "&&", NULL};
	char **all_flags = all_f_gene;
	int i = 0;

	if (!next_deli)
		return (8);
	for (i = 0; all_flags[i] != NULL; i++)
		if (!_strcmp_c(next_deli, all_flags[i]))
			break;

	return (i);
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
int exe_one_command(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head)
{
	int flag_terminator = 0, error = 0;

	switch (sign_com_pos(copy_head->prev->next_deli))
	{
	case 0: /* >> */
		error = redir_output_append(head, tok_com, status);
		break;
	case 1: /* > */
		error = redir_output(head, tok_com, status);
		break;
	case 2: /* << */
		flag_terminator = redir_input_heredoc(tokens, cc, en, av,
			status, head, tok_com, copy_head);
		break;
	case 3: /* < */
		flag_terminator = redir_input(tokens, cc, en, av, status, head,
			tok_com, copy_head);
		break;
	case 4: /* || */
		flag_terminator = or_condition(tokens, cc, en, av, status, head,
			tok_com, copy_head);
		break;
	case 5: /* | */
		flag_terminator = out_redir_in(tokens, cc, en, av, status, head,
			tok_com, copy_head);
		break;
	case 6: /* ; */
		exe_multi_commands(tokens, cc, en, av, status, head,
			tok_com, copy_head);
		break;
	case 7: /* && */
		flag_terminator = and_condition(tokens, cc, en, av, status,
			head, tok_com, copy_head);
		break;
	}
	if (error == EXIT_IS_DIR || error == EXIT_NOT_ACCESS)
	{
		print_error(av[0], *cc, (*tok_com)[0], error);
	}
	return (flag_terminator);
}

/**
* createandexesh - creat and execute the command given by user
* @tokens: strings from stdin
* @cc: is the counter of commans executes by user
* @en: list containing the end parameter for execve syscall
* @av: list containing the arguments given by user
* @status: previous loop status
* @head: first element of the list of commands
* Return: the process status
*/
int exe_mul_commands(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head)
{
	dlistint_t *copy_head = NULL;
	char ***tok_com = NULL;
	int flag_terminator = 0, sign_command_pos = 0;

	copy_head = *head;
	while (copy_head)
	{
		tok_com = &(copy_head->tokens);
		sign_command_pos = sign_com_pos(copy_head->next_deli);
		if (copy_head->prev)
			flag_terminator = exe_one_command(tokens, cc, en, av,
				status, head, tok_com, copy_head);
		else
			if (sign_command_pos < 2 || sign_command_pos > 3)
				createandexesh(tokens, cc, en, av, status, head,
					tok_com, copy_head);

		if (sign_command_pos > 3 && sign_command_pos != 5)
			if (copy_head->buffer_in)
			{
				printf("%s", copy_head->buffer_in);
				fflush(stdout);
			}
		if (flag_terminator)
			break;
		copy_head = copy_head->next;
	}
	return (0);
}
