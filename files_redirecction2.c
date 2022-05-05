#include "headersh.h"

/**
* stdin_to_file - open a file with read mode
* @filename: file name
* Return: status program
*/
int stdin_to_file(char *filename)
{
	int fd = 0;

	fd = open(filename, O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (errno + 1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
