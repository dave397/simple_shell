#include "main.h"

/**
 * hsh - main shell loop
 * @global: the parameter & return global struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int simple_shell(global_t *global, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_global(global);
		if (is_terminal(global))
			_puts("$ ");
		_eputchar(-1);
		r = get_input(global);
		if (r != -1)
		{
			set_global(global, av);
			builtin_ret = find_builtin(global);
			if (builtin_ret == -1)
				_find(global);
		}
		else if (is_terminal(global))
			_putchar('\n');
		free_global(global, 0);
	}
	write_history(global);
	free_global(global, 1);
	if (!is_terminal(global) && global->status)
		exit(global->status);
	if (builtin_ret == -2)
	{
		if (global->err_num == -1)
			exit(global->status);
		exit(global->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @global: the parameter & return global struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(global_t *global)
{
	int i, built_in_ret = -1;
	inbuilt_t builtintbl[] = {{"exit", _mexit},
				  {"env", _myenv},
				  {"history", _myhistory},
				  {"setenv", _mysetenv},
				  {"unsetenv", _myunsetenv},
				  {"cd", _cd},
				  {NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(global->av[0], builtintbl[i].type) == 0)
		{
			global->line_count++;
			built_in_ret = builtintbl[i].func(global);
			break;
		}
	return (built_in_ret);
}

/**
 * _find - finds a command in PATH
 * @global: the parameter & return global struct
 *
 * Return: void
 */
void _find(global_t *global)
{
	char *path = NULL;
	int i, k;

	global->path = global->av[0];
	if (global->linecount_flag == 1)
	{
		global->line_count++;
		global->linecount_flag = 0;
	}
	for (i = 0, k = 0; global->arg[i]; i++)
		if (!is_separator(global->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(global, _getenv(global, "PATH="), global->av[0]);
	if (path)
	{
		global->path = path;
		_fork(global);
	}
	else
	{
		if ((is_terminal(global) || _getenv(global, "PATH=") ||
		     global->av[0][0] == '/') &&
		    _is_cmd(global, global->av[0]))
			_fork(global);
		else if (*(global->arg) != '\n')
		{
			global->status = 127;
			print_error(global, "not found\n");
		}
	}
}

/**
 * _fork - forks a an exec thread to run cmd
 * @global: the parameter & return global struct
 *
 * Return: void
 */
void _fork(global_t *global)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(global->path, global->av,
			   retrieve_environ(global)) == -1)
		{
			free_global(global, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(global->status));
		if (WIFEXITED(global->status))
		{
			global->status = WEXITSTATUS(global->status);
			if (global->status == 126)
				print_error(global, "Permission denied\n");
		}
	}
}
