#include "headersh.h"

/**
* parsesh - split what is inside of buffer
* @buffer: store the data get it
* @tokens: store the string user wrote
* @len: length of tokens
* @status: execute status
* Return: nothing
*/

void parsesh(char **buffer, int *len, char ***tokens, int *status)
{
	char *token;
	int i;
	const char delim[] = " \t\n\"";

	(void)status;
	*tokens = malloc(sizeof(char *) * (*len + 1));
	if (*tokens == NULL)
	{
		printf("Error\n");
		return;
	}
	token = strtok(*buffer, delim);
	for (i = 0; token != NULL; i++)
	{
		(*tokens)[i] = token;
		token = strtok(NULL, delim);
	}
	(*tokens)[i] = token;
}
