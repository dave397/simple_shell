#include "main.h"

/**
 * _myexit - exits the shell
 * @global: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if global.av[0] != "exit"
 */
int _myexit(global_t *global)
{
	int exitcheck;

	if (global->av[1]) /* If there is an exit arguement */
	{
		exitcheck = _erratoi(global->av[1]);
		if (exitcheck == -1)
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
 * _mycd - changes the current directory of the process
 * @global: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(global_t *global)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s) _puts("TODO: >>getcwd failure emsg here<<\n");
	if (!global->av[1])
	{
		dir = _getenv(global, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
			    chdir((dir = _getenv(global, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(global->av[1], "-") == 0)
	{
		if (!_getenv(global, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(global, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
		    chdir((dir = _getenv(global, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(global->av[1]);
	if (chdir_ret == -1)
	{
		print_error(global, "can't cd to ");
		_eputs(global->av[1]), _eputchar('\n');
	}
	else
	{
		_setenv(global, "OLDPWD", _getenv(global, "PWD="));
		_setenv(global, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @global: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(global_t *global)
{
	char **arg_array;

	arg_array = global->av;
	_puts("help call works. Function not yet implemented \n");
	if (0) _puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
