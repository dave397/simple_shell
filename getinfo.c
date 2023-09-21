#include "main.h"

/**
 * clear_info - initializes global_t struct
 * @global: struct address
 */
void clear_info(global_t *global)
{
	global->arg = NULL;
	global->av = NULL;
	global->path = NULL;
	global->argc = 0;
}

/**
 * set_info - initializes global_t struct
 * @global: struct address
 * @av: argument vector
 */
void set_info(global_t *global, char **av)
{
	int i = 0;

	global->fname = av[0];
	if (global->arg)
	{
		global->av = _strtok(global->arg, " \t");
		if (!global->av)
		{

			global->av = malloc(sizeof(char *) * 2);
			if (global->av)
			{
				global->av[0] = _strdup(global->arg);
				global->av[1] = NULL;
			}
		}
		for (i = 0; global->av && global->av[i]; i++)
			;
		global->argc = i;

		replace_alias(global);
		replace_vars(global);
	}
}

/**
 * free_info - frees global_t struct fields
 * @global: struct address
 * @all: true if freeing all fields
 */
void free_info(global_t *global, int all)
{
	ffree(global->av);
	global->av = NULL;
	global->path = NULL;
	if (all)
	{
		if (!global->cmd_buf)
			free(global->arg);
		if (global->env)
			free_list(&(global->env));
		if (global->history)
			free_list(&(global->history));
		if (global->alias)
			free_list(&(global->alias));
		ffree(global->environ);
			global->environ = NULL;
		bfree((void **)global->cmd_buf);
		if (global->readfd > 2)
			close(global->readfd);
		_putchar(-1);
	}
}
