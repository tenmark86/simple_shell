#include "headersh.h"

/**
* open_errors_continue - prints output error
* @av: first parameter that called the shell
* @cc: error counter
* @tok: command inputed by user
* @errmsg: identifier of eroor message to print
* Return: nothing
*/
void open_errors_continue(char *av, int cc, char *tok, int errmsg)
{
	char strnum[11];
	char *message = NULL, *cc_str;
	int av_len = 0, tok_len = 0, msg_len = 0, cc_len = 0;

	cc_str = _itoa(cc, strnum);
	cc_len = _strlen(cc_str);
	av_len = _strlen(av);
	tok_len = _strlen(tok);

	if (errmsg == EXIT_NOT_EXIST)
	{
		msg_len = (38 + av_len + tok_len + cc_len);
		message = malloc(sizeof(char) * (msg_len + 1));
		message[0] = '\0';
		_strcat(message, av);
		_strcat(message, ": ");
		_strcat(message, cc_str);
		_strcat(message, ": cannot open ");
		_strcat(message, tok);
		_strcat(message, ": ");
		_strcat(message, "No such file\n");
		write(STDERR_FILENO, message, msg_len);
	}
	free(message);
}

/**
* open_errors - prints output error
* @av: first parameter that called the shell
* @cc: error counter
* @tok: command inputed by user
* @errmsg: identifier of eroor message to print
* Return: nothing
*/
void open_errors(char *av, int cc, char *tok, int errmsg)
{
	char strnum[11];
	char *message = NULL, *cc_str;
	int av_len = 0, tok_len = 0, msg_len = 0, cc_len = 0;

	cc_str = _itoa(cc, strnum);
	cc_len = _strlen(cc_str);
	av_len = _strlen(av);
	tok_len = _strlen(tok);

	if (errmsg == EXIT_NOT_ACCESS)
	{
		msg_len = (38 + av_len + tok_len + cc_len);
		message = malloc(sizeof(char) * (msg_len + 1));
		message[0] = '\0';
		_strcat(message, av);
		_strcat(message, ": ");
		_strcat(message, cc_str);
		_strcat(message, ": cannot create ");
		_strcat(message, tok);
		_strcat(message, ": ");
		_strcat(message, "Permission denied\n");
		write(STDERR_FILENO, message, msg_len);
	}
	else if (errmsg == EXIT_IS_DIR)
	{
		msg_len = (35 + av_len + tok_len + cc_len);
		message = malloc(sizeof(char) * (msg_len + 1));
		message[0] = '\0';
		_strcat(message, av);
		_strcat(message, ": ");
		_strcat(message, cc_str);
		_strcat(message, ": cannot create ");
		_strcat(message, tok);
		_strcat(message, ": ");
		_strcat(message, "Is a directory\n");
		write(STDERR_FILENO, message, msg_len);
	}
	else
		open_errors_continue(av, cc, tok, errmsg);
	free(message);
}
