#include "headersh.h"

/**
* free_tok - frees the @tokens string
* @command: string containing the parsed input line
* Return: nothing
*/
void free_tok(char *command)
{
	free(command);
}

/**
* _itoa - takes an int and converts it to a string
* @num: int passed to function
* @strnum: string to be converted
* Return: the converted string
*/
char *_itoa(int num, char *strnum)
{
	int copy_num = num, i, j, div = 1;

	for (i = 0; copy_num != 0; i++)
		copy_num /= 10;
	j = i;
	while (i != 0)
	{
		div *= 10;
		i--;
	}
	div /= 10;
	for (i = 0; i < j; i++)
	{
		strnum[i] = (num / div) + '0';
		num %= div;
		div /= 10;
	}
	strnum[i] = '\0';
	return (strnum);
}

/**
* print_error - prints output error
* @av: first parameter that called the shell
* @cc: error counter
* @tok: command inputed by user
* @errmsg: identifier of eroor message to print
* Return: nothing
*/
void print_error(char *av, int cc, char *tok, int errmsg)
{
	char strnum[11];
	char *message = NULL, *cc_str;
	int av_len = 0, tok_len = 0, msg_len = 0, cc_len = 0;

	cc_str = _itoa(cc, strnum);
	cc_len = _strlen(cc_str);
	av_len = _strlen(av);
	tok_len = _strlen(tok);
	if (errmsg == 1)
	{
		msg_len = (16 + av_len + tok_len + cc_len);
		message = malloc(sizeof(char) * (msg_len + 1));
		message[0] = '\0';
		_strcat(message, av);
		_strcat(message, ": ");
		_strcat(message, cc_str);
		_strcat(message, ": ");
		_strcat(message, tok);
		_strcat(message, ": ");
		_strcat(message, "not found\n");
		write(STDERR_FILENO, message, msg_len);
	}
	if (errmsg == 0)
	{
		msg_len = (24 + av_len + tok_len + cc_len);
		message = malloc(sizeof(char) * (msg_len + 1));
		message[0] = '\0';
		_strcat(message, av);
		_strcat(message, ": ");
		_strcat(message, cc_str);
		_strcat(message, ": ");
		_strcat(message, tok);
		_strcat(message, ": ");
		_strcat(message, "Permission denied\n");
		write(STDERR_FILENO, message, msg_len);
	}
	free(message);
}

/**
* check_command - creat and execute the command given by user
* @tokens: strings from stdin
* @cc: is the counter of commans executes by user
* @en: list containing the end parameter for execve syscall
* @av: list containing the arguments given by user
* @statuss: previous loop status
* Return: the process status
*/

int check_command(char ***tokens, int *cc, char ***en, char **av, int *statuss)
{
	int statu = 0;
	char **buffer = *tokens, *tok = NULL;
	struct stat st;

	st.st_mode = 0;
	statu = built_ins_sh(tokens, en, buffer, statuss, av, cc);
	if (statu != 0)
		return (2);
	statu = add_path(tokens, *en);
	if (statu == 127)
	{
		print_error(av[0], *cc, (*tokens)[0], 1);
		return (statu);
	}
	tok = (*tokens)[0];
	stat(tok, &st);
	if ((access(tok, F_OK | X_OK) == 0) &&
		((st.st_mode & S_IFMT) == S_IFREG))
	{
		return (statu);
	}
	else
	{
		if ((st.st_mode & S_IFMT) == S_IFDIR)
		{
			print_error(av[0], *cc, tok, 0);
			return (126);
		}
		if (access(tok, F_OK) != 0)
		{
			print_error(av[0], *cc, tok, 1);
			return (127);
		}
		else if (access(tok, X_OK) != 0)
		{
			print_error(av[0], *cc, tok, 0);
			return (126);
		}
	}
	return (0);
}

/**
* createandexesh - creat and execute the command given by user
* @tokens: strings from stdin
* @cc: is the counter of commans executes by user
* @en: list containing the end parameter for execve syscall
* @av: list containing the arguments given by user
* @statuss: previous loop status
* Return: the process status
*/
int createandexesh(char ***tokens, int *cc, char ***en, char **av,
	int *statuss)
{
	pid_t child_pid;
	int wait_status = 0, statu = 0, exit_stat = 0;
	char *command = **tokens, *trans;

	statu = check_command(tokens, cc, en, av, statuss);
	if (statu != 0 && statu != 1)
	{
		if (statu != 2)
			*statuss = statu;
		return (statu);
	}
	trans = (*tokens)[0], (*tokens)[0] = command, command = trans;
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		*statuss = 1;
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(command, *tokens, *en) == -1)
		{
			if (statu == 1)
				free_tok(command);
			exit(127);
		}
	}
	else
	{
		waitpid(child_pid, &wait_status, 0);
		if (WIFEXITED(wait_status))
			exit_stat = WEXITSTATUS(wait_status);
	}
	if (statu == 1)
		free_tok(command);
	*statuss = exit_stat;
	return (exit_stat);
}
