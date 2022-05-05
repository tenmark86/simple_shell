#include "headersh.h"

/**
 * envdup - duplicates the env list
 * @env: is the env list to be duplicated
 * Return: a new allocated env list, or NULL on fail
 */
char **envdup(char **env)
{
	char **new = NULL, *buf = NULL;
	size_t size = 0, b_size = 0, i = 0, b_i = 0;

	if (!env || !(*env))
		return (NULL);
	while (env[size])
		size++;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	for (i = 0; i < size; i++)
	{
		b_size = 0;
		while (env[i][b_size])
			b_size++;
		buf = (char *)malloc(sizeof(char) * (b_size + 1));
		for (b_i = 0; b_i <= b_size; b_i++)
			buf[b_i] = env[i][b_i];
		new[i] = buf;
	}
	new[i] = NULL;
	return (new);
}
/**
 * freeenv - free an env copy
 * @env: is the env list
 */
void freeenv(char **env)
{
	int i = 0;

	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
