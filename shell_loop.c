#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * hsh - main loop
 * @info: info struct and parameter to be returned
 * @avent: argument vector
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_val *info, char **avent)
{
	ssize_t valrun = 0;
	int builtin_ret = 0;

	while (valrun != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		valrun = get_input(info);
		if (valrun != -1)
		{
			set_info(info, avent);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}


/**
 * find_builtin - Write a fucntion that finds a builtin command
 * @info: info struct and parameter
 *
 * Return: -1 if builtin not found, 0 if builtin executed successfully
 * or 1 if builtin found but not successful, -2 if builtin signals exit()
 */
int find_builtin(info_val *info)
{
	int valin, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (valin = 0; builtintbl[valin].type; valin++)
		if (_strcmp(info->argv[0], builtintbl[valin].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[valin].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - write a function finds a command in the PATH
 * @info: info struct returned and the parameter
 *
 * Return: 0
 */
void find_cmd(info_val *info)
{
	char *path = NULL;
	int valin, valkin;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (valin = 0, valkin = 0; info->arg[valin]; valin++)
		if (!is_delim(info->arg[valin], " \t\n"))
			valkin++;
	if (!valkin)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - A function that forks exec thread to run the cmd
 * @info: info struct to be returned
 *
 * Return: nothing
 */
void fork_cmd(info_val *info)
{
	pid_t chi_pid;

	chi_pid = fork();
	if (chi_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (chi_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
