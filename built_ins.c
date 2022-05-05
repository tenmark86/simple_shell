#include "headersh.h"

/**
* env - fills memory with a constant byte
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* Return: nothing
*/

int env(char ***en, char ***tokens, char **buffer, int *statuss, char **av, int *cc)
{
	int i, j;

	(void)tokens, (void)buffer, (void)statuss, (void)av, (void)cc;
	for (i = 0; (*en)[i] != NULL; i++)
	{
		for (j = 0; (*en)[i][j] != '\0'; j++)
			continue;
		write(STDOUT_FILENO, (*en)[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
}

/**
 * _atoi - convert a string into a integer.
 * @s: string
 * @is_number: check if is a number
 * Return: the representation of the string in integer.
 */
int _atoi(char *s, int *is_number)
{
	int negative = 1, i = 0;
	unsigned int numero = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			negative *= -1;
		else if (s[i] > 57 || s[i] < 48)
		{
			*is_number = 1;
			return (0);
		}
		else if (s[i] >= 0 + '0' && s[i] < 10 + '0')
			numero = numero * 10 + (s[i] - '0');
		else if (s[i - 1] >= 0 + '0' && s[i - 1] < 10 + '0')
			break;
	}
	return (numero * negative);
}

/**
* exi - fills memory with a constant byte
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* Return: nothing
*/

int exi(char ***en, char ***tokens, char **buffer, int *statuss, char **av, int *cc)
{
	int s = *statuss, is_number = 0;
	char err_message[] = "Illegal number: ";

	(void)av, (void)cc;
	if ((*tokens)[1])
	{
		s = _atoi((*tokens)[1], &is_number);
		if (s < 0 || is_number == 1)
		{
			print_error_builtin(*av, *cc, *tokens, err_message);
			*statuss = 2;
			return (1);
		}
	}
	free_all(buffer, tokens);
	freeenv(*en);
	exit(s);
}

/**
* cd - changes the current working directory
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* Return: nothing
*/

int cd(char ***en, char ***tokens, char **buffer, int *statuss, char **av, int *cc)
{
	int ret = 0;
	char *_set[3];
	char *home_env = NULL, *prewd = NULL, **set = _set;

	(void)buffer, (void)av, (void)cc;
	home_env = _getenv("HOME", *en);
	if (!(*tokens)[1])
		ret = chdir(home_env);
	else
	{
		prewd = _getenv("OLDPWD", *en);
		if (!((*tokens)[1][0] == '-'))
		{
			if (!prewd)
			{
				perror("-hsh: cd: OLDPWD not set");
				*statuss = 1;
				return (0);
			}
			ret = chdir(prewd);
		}
		else
		{
			ret = chdir((*tokens)[1]);
		}
		set[0] = NULL;
		set[1] = "OLDPWD";
		set[2] = _getenv("PWD", *en);
		_setenv(en, &set, buffer, statuss, av, cc);
	}
	return (!ret);
}

/**
* built_ins_sh - fills memory with a constant byte
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* Return: numbers of characters printed
*/

int built_ins_sh(char ***tokens, char ***en, char **buffer, int *statuss, char **av, int *cc)
{
	int j;
	op_t o[] = {
		{ "env", env },
		{ "exit", exi },
		{ "cd", cd },
		{ "unsetenv", _unsetenv },
		{ "setenv", _setenv },
		{ NULL, NULL },
	};

	for (j = 0; o[j].op != NULL; j++)
		if (_strcmp((*tokens)[0], o[j].op) == 0)
			return (o[j].f(en, tokens, buffer, statuss, av, cc));
	return (0);
}
