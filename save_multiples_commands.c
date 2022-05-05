#include "headersh.h"

/**
* add_dnodeint_end - add a node at the end of a double linked list
* @head: header of double linked list
* Return: address of a new element
*/
dlistint_t *add_dnodeint_end(dlistint_t **head)
{
	dlistint_t *new, *headcopy;

	headcopy = *head;

	if (head == NULL)
		return (NULL);

	new = malloc(sizeof(dlistint_t));
	if (new == NULL)
		return (NULL);

	new->buffer_in = NULL;
	new->next_deli = NULL;
	new->tokens = NULL;
	new->status = 0;

	if (*head == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		*head = new;
	}
	else
	{
		while (headcopy->next != NULL)
			headcopy = headcopy->next;
		new->next = NULL;
		new->prev = headcopy;
		headcopy->next = new;
	}

	return (new);
}

/**
* free_dlistint - free a double linked list
* @head: header of double linked list
* Return: nothing
*/
void free_dlistint(dlistint_t *head)
{
	dlistint_t *savepoin;

	if (head != NULL)
	{
		while (head->prev != NULL)
			head = head->prev;

		while (head != NULL)
		{
			savepoin = head->next;
			if (head->tokens)
				free(head->tokens);
			if (head->buffer_in)
				free(head->buffer_in);
			free(head);
			head = savepoin;
		}
	}
}

/**
* realloc_tokens - add more args to a command.
* @tokens: command
* @word: string to add to command
* Return: memory address of the realloc otherwise NULL.
*/
char **realloc_tokens(char **tokens, char *word)
{
	int index = 0;
	char **new_tokens = NULL;

	if (!tokens)
	{
		new_tokens = malloc(sizeof(char *) * 2);
		if (!new_tokens)
			return (NULL);
		new_tokens[0] = word;
		new_tokens[1] = NULL;
		return (new_tokens);
	}
	for (index = 0; tokens[index]; index++)
		continue;
	new_tokens = malloc(sizeof(char *) * (index + 2));
	if (!new_tokens)
		return (NULL);
	for (index = 0; tokens[index]; index++)
		new_tokens[index] = tokens[index];
	new_tokens[index] = word;
	new_tokens[index + 1] = NULL;
	free(tokens);

	return (new_tokens);
}

/**
* save_mul_commands - save multiples commands in a double linked list.
* @head: first element of the array of commands
* @tokens: all string got in getline
* @status: error variable
* Return: 1 on success otherwise 0.
*/
int save_mul_commands(dlistint_t **head, char ***tokens, int *status)
{
	int i = 0, j = 0, flag_deli = 0;
	dlistint_t *new_node = NULL;
	char *all_f_gene[] = {">", ">>", "<", "<<", "|", ";", "&&", "||", NULL};
	char **all_flags = all_f_gene;

	new_node = add_dnodeint_end(head);
	for (i = 0; (*tokens)[i] != NULL; i++)
	{
		flag_deli = 0;
		for (j = 0; all_flags[j] != NULL; j++)
		{
			if (!_strcmp((*tokens)[i], all_flags[j]))
			{
				flag_deli = 1;
				break;
			}
		}
		if (flag_deli)
			new_node->next_deli = (*tokens)[i];
		else
		{
			new_node->tokens = realloc_tokens(new_node->tokens,
				(*tokens)[i]);
			if (!new_node->tokens)
			{
				*status = 1;
				return (1);
			}
		}
		if ((*tokens)[i + 1] != NULL && flag_deli)
			new_node = add_dnodeint_end(head);
	}
	return (0);
}
