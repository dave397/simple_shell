#include "main.h"

/**
 * retrieve_environ - returns the string array copy of our environ
 * @global: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **retrieve_environ(global_t *global)
{
	if (!global->environ || global->env_changed)
	{
		global->environ = env_to_strings(global->env);
		global->env_changed = 0;
	}

	return (global->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @global: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(global_t *global, char *var)
{
	env_t *node = global->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			global->env_changed =
			    delete_node_at_index(&(global->env), i);
			i = 0;
			node = global->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (global->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @global: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(global_t *global, char *var, char *value)
{
	char *buf = NULL;
	env_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = global->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			global->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(global->env), buf, 0);
	free(buf);
	global->env_changed = 1;
	return (0);
}
