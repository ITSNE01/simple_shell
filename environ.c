#include "shell.h"

/**
 * _myenv - prints the current environment variables
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Retrieves the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype
 * @name: Name of the environment variable to retrieve
 *
 * Return: The value of the environment variable if found, NULL otherwise
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
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
 * _mysetenv - Initializes a new environment variable,
 *             or modifies an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype
 *  Return: 0 on success, 1 on failure
 *
 * This function expects exactly two arguments:
 * - info->argv[1]: Name of the environment variable
 * - info->argv[2]: Value of the environment variable
 * It sets the environment variable by calling _setenv
 * If the number of args is incorrect, it prints an error message
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Removes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * Return: 0 on success, 1 on failure.
 *
 * This function expects at least one argument:
 * - info->argv[1...n]: Names of the environment variables to remove
 * It removes each specified environment variable by calling _unsetenv
 * If no variables are specified, it prints an error message
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Populates the environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
