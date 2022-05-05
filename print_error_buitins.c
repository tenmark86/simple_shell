#include "headersh.h"

/**
* print_error_builtin - prints output error
* @av: first parameter that called the shell
* @cc: error counter
* @token: command inputed by user
* @errmsg: identifier of eroor message to print
* Return: nothing
*/
void print_error_builtin(char *av, int cc, char **token, char *errmsg)
{
	fprintf(stderr, "%s: %d: %s: %s%s\n", av, cc,
		token[0], errmsg, token[1]);
}
