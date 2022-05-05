#include "headersh.h"

/**
* main - call the shell by Arturo and Juani
* @ac: argument count
* @av: argument vector
* @env: external variable environment parsed by lines
* Return: nothing
*/
int main(int ac, char **av, char **env)
{
	int status = 0;
	char **en = NULL;

	if (ac == 1)
	{
		en = envdup(env);
		status = simple_sh(av, &en);
		freeenv(en);
		return (status);
	}
	return (0);
}
