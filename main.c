#include "main.h"

/**
 * handle_error - handles error
 * Return: void
 */

void handle_error()
{
	if (errno == ENOENT)
	{
		perror("Error");
		exit(127);
	}
	if (errno == EACCES) exit(126);
	exit(1);
}

/**
 * open_file - opens file
 * @file_name: name of file
 * Return: The file descriptor if successful, or -1 on error
 */
int open_file(char *file_name)
{
	int file_descriptor = open(file_name, O_RDONLY);
	if (file_descriptor >= 0) return file_descriptor;
	handle_error();
	return -1;
}

/**
 * main - entry point
 * @arg_count: arg count
 * @arg_val: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arg_count, char **arg_val)
{
	global_t global[] = {INIT};

	int file_descriptor = 2;

	file_descriptor += 3;

	if (arg_count == 2)
	{
		file_descriptor = open_file(arg_val[1]);
		global->readfd = file_descriptor;
	}
	populate_env_list(global);
	check_history(global);
	simple_shell(global, arg_val);
	return (0);
}
