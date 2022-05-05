#include "headersh.h"

/**
 * _getenv - gets @variable_env's information after the '='
 * @variable_env: String specifying which variable to get information for
 * @en: pointer list containing the environment variable parsed by lines
 * Return: @variable_env's information after the '=' on success, NULL otherwise
 */
char *_getenv(const char *variable_env, char **en)
{
	int i, j, flag = 1;

	if (en == NULL)
		return (NULL);
	for (i = 0; en[i] != NULL; i++, flag = 1)
	{
		for (j = 0; en[i][j] != '='; j++)
		{
			if (variable_env[j] != en[i][j])
			{
				flag = 0;
				break;
			}
		}
		if (flag != 0)
			return (&(en[i][j + 1]));
	}
	return (NULL);
}
