#include "main.h"

/**
 * _mexit - exits the shell
 * @global: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: exits with a given exit status
 *         (0) if global.av[0] != "exit"
 */
int _mexit(global_t *global)
{
	int exit;

	if (global->av[1]) /* If there is an exit arguement */
	{
		exit = _erratoi(global->av[1]);
		if (exit == -1)
		{
			global->status = 2;
			print_error(global, "Illegal number: ");
			_eputs(global->av[1]);
			_eputchar('\n');
			return (1);
		}
		global->err_num = _erratoi(global->av[1]);
		return (-2);
	}
	global->err_num = -1;
	return (-2);
}

/**
 * _cd - changes the current directory
 * @global: arguments.
 * Return: Always 0
 */
int _cd(global_t *global)
{
	char *new_dir = NULL;
	char buffer[1024];

	if (global->av[1] == NULL)
	{
		new_dir = _getenv(global, "HOME=");
	}
	else if (_strcmp(global->av[1], "-") == 0)
	{
		new_dir = _getenv(global, "OLDPWD=");
		if (new_dir == NULL)
		{
			_puts("OLDPWD not set\n");
			return (1);
		}
		_puts(new_dir);
		_putchar('\n');
	}
	else
	{
		new_dir = global->av[1];
	}
	if (new_dir == NULL)
	{
		_puts("HOME not set\n");
		return (1);
	}
	if (chdir(new_dir) == -1)
	{
		print_error(global, "can't cd to ");
		_eputs(new_dir);
		_eputchar('\n');
	}
	else
	{
		_setenv(global, "OLDPWD", _getenv(global, "PWD="));
		_setenv(global, "PWD", getcwd(buffer, sizeof(buffer)));
	}

	return (0);
}
