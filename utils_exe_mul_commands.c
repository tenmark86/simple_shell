#include "headersh.h"

/**
* create_pipe - create pipe
* @pipefd: pipe array
* Return: the process status
*/
int create_pipe(int (*pipefd)[2])
{
	if (pipe(*pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
* read_command_output - save the command output of the command
* @pipefd: pipe array
* @cur_node: current command node
* Return: the process status
*/
int read_command_output(int *pipefd, dlistint_t *cur_node)
{
	char buff[1025] = "";
	int i = 0;

	close(pipefd[1]);
	for (i = 0; i < 1025; i++)
		buff[i] = '\0';
	while (read(pipefd[0], &buff, 1024) > 0)
	{
		realloc_buffer(&(cur_node->buffer_in), buff);
		for (i = 0; i < 1025; i++)
			buff[i] = '\0';
	}
	close(pipefd[0]);
	return (0);
}

/**
* change_output_command - change the stdout for end write pipe
* @pipefd: pipe array
* Return: the process status
*/
int change_output_command(int *pipefd)
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	close(pipefd[1]);
	return (0);
}

/**
* realloc_buffer - add more strings to the buffer
* @buffer: output command
* @str: string to put on the bufffer
* Return: the process status
*/
int realloc_buffer(char **buffer, char *str)
{
	char *new_buffer = NULL;
	int size_buffer = 0, size_str = 0, i = 0;

	if (!str || str[0] == '\0')
		return (0);
	for (size_buffer = 0; *buffer && (*buffer)[size_buffer]; size_buffer++)
		continue;
	for (size_str = 0; str && str[size_str]; size_str++)
		continue;
	new_buffer = malloc(sizeof(char) * (size_str + size_buffer + 1));
	if (!new_buffer)
		return (1);
	for (i = 0; i < size_buffer + size_str; i++)
	{
		if (i < size_buffer)
			new_buffer[i] = (*buffer)[i];
		else
			new_buffer[i] = str[i - size_buffer];
	}
	new_buffer[i] = '\0';
	if (*buffer)
		free(*buffer);
	*buffer = new_buffer;
	return (0);
}
