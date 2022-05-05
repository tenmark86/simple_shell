#include "headersh.h"

/**
* set_normal_stdout - set the stdout in fd 1
* @stdout_copy: stdout old file descriptor
* Return: status program
*/
int set_normal_stdout(int stdout_copy)
{
	if (dup2(stdout_copy, 1) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
* set_normal_stdin - set the stdin in fd 0
* @stdin_copy: stdout old file descriptor
* Return: status program
*/
int set_normal_stdin(int stdin_copy)
{
	if (dup2(stdin_copy, 0) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
* stdout_to_file - open a file with write mode
* @filename: file name
* Return: status program
*/
int stdout_to_file(char *filename)
{
	int fd = 0;

	fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (errno + 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

/**
* stdout_to_end_file - open a file with append mode
* @filename: file name
* Return: status program
*/
int stdout_to_end_file(char *filename)
{
	int fd = 0;

	fd = open(filename, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (errno + 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

/**
* stdout_to_stdin - open a file with append mode
* @pipefd: file name
* Return: status program
*/
int stdout_to_stdin(int *pipefd)
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
