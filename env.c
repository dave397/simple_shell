#include "main.h"

/**
 * _myenv - prints the current environment
 * @global: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(global_t *global)
{
	print_list_str(global->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @global: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(global_t *global, const char *name)
{
	env_t *node = global->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @global: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(global_t *global)
{
	if (global->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(global, global->av[1], global->av[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @global: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(global_t *global)
{
	int i;

	if (global->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= global->argc; i++)
		_unsetenv(global, global->av[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @global: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(global_t *global)
{
	env_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	global->env = node;
	return (0);
}
