/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_modes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:48:10 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:31:47 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // t_sym_tab, g_sym_table
#include "libft.h" // free, ft_strncmp, ft_strlen, ft_putstr_fd
#include "../../utils.h" // ft_perror, get_value
#include "cd_private.h" // check_for_dots, set_path, get_path
#include <errno.h> // errno
#include <unistd.h> // chdir, getcwd
#include <stdio.h> // perror

static int	cd_oldpwd(char *var, char *oldpwd);
static int	cd_back(int count, int i, char *path, char *cwd);

/**
 * It handles the case where the user enters `cd -` as a command
 * 
 * @param oldpwd the oldpwd variable from the environment
 * 
 * @return The return value is the status of the cd command.
 */
int	handle_dash(char *oldpwd)
{
	t_sym_tab	*temp;
	int			status;

	if (*g_sym_table == NULL)
		temp = NULL;
	else
		temp = *g_sym_table;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->var, "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			status = cd_oldpwd(temp->var, oldpwd);
			return (status);
		}
		temp = temp->next;
	}
	ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
	return (1);
}

/**
 * It checks for the presence of `..` in the path, and if it finds it, 
 * it changes the current working
 * directory to the parent directory of the current working directory
 * 
 * @param path The path to the directory we're trying to cd to.
 * 
 * @return The return value is the status of the cd_back function.
 */
int	handle_dots(char *path)
{
	int		i;
	int		count;
	int		status;
	char	*cwd;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (errno);
	set_path("OLDPWD", cwd);
	count = check_for_dots(path, &i);
	status = cd_back(count, i, path, cwd);
	free(cwd);
	return (status);
}

/**
 * It changes the current working directory to the value of the OLDPWD 
 * environment variable, and sets
 * the OLDPWD environment variable to the current working directory
 * 
 * @param var the name of the environment variable to get the value of.
 * @param oldpwd the current working directory
 * 
 * @return The return value of the function is the error number.
 */
static int	cd_oldpwd(char *var, char *oldpwd)
{
	char	*path;

	path = get_value(var);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(path) != 0)
	{
		ft_perror("cd", path);
		free(path);
		return (errno);
	}
	set_path("OLDPWD", oldpwd);
	printf("%s\n", path);
	free(path);
	return (0);
}

/**
 * It changes the current working directory to the previous directory, 
 * and then changes it to the directory specified by the path
 * 
 * @param count the number of times we need to go back
 * @param i the index of the path string
 * @param path the path to the directory to change to
 * @param cwd current working directory
 * 
 * @return The return value of the function.
 */
static int	cd_back(int count, int i, char *path, char *cwd)
{
	while (count != 0)
	{
		if (change_prev_dir() != 0)
		{
			ft_perror("cd", path);
			return (errno);
		}
		count--;
	}
	if ((int)ft_strlen(path) > i)
	{
		if (chdir(&path[i]) != 0)
		{
			if (chdir(cwd) != 0)
				ft_perror("cd", cwd);
			ft_perror("cd", path);
			return (errno);
		}
	}
	return (0);
}

/**
 * It changes the current working directory to the value of 
 * the HOME environment variable
 * 
 * @return The return value is the error number.
 */
int	cd_home(void)
{
	t_sym_tab	*temp;
	char		*path;

	temp = *g_sym_table;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->var, "HOME=", ft_strlen("HOME=")) == 0)
		{
			path = get_value(temp->var);
			if (path == NULL)
				break ;
			if (chdir(path) != 0)
			{
				free(path);
				return (errno);
			}
			free(path);
			return (0);
		}
		temp = temp->next;
	}
	ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	return (1);
}
