/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:50:47 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:18:55 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // t_sym_tab
#include "libft.h" // ft_strncmp, ft_strlen
#include "cd_private.h" // handle_dash, handle_dots, set_path, cd_home
#include "../../utils.h" // ft_strcmp, ft_perror
#include <stdio.h> // printf, perror
#include <unistd.h> // chdir, getcwd
#include <errno.h> // errno

static int	exec_cd(char *path, char *oldpwd);

/**
 * It changes the current working directory to the directory specified by 
 * the first argument, or to the home directory if no argument is given
 * 
 * @param argv The arguments passed to the command.
 * 
 * @return The return value of the function is the status of the cd command.
 */
int	cd_b(char **argv)
{
	int			status;
	char		*path;
	char		*oldpwd;

	status = 0;
	oldpwd = getcwd(NULL, 0);
	if (argv[1] == NULL)
	{
		status = cd_home();
		if (status == 0)
			set_path("OLDPWD", oldpwd);
		return (status);
	}
	path = argv[1];
	if (oldpwd == NULL)
		return (errno);
	status = exec_cd(path, oldpwd);
	return (status);
}

/**
 * It changes the current working directory to the one specified by the user
 * 
 * @param path the path to change to
 * @param oldpwd the old working directory
 * 
 * @return The return value of the function is the status of the function.
 */
static int	exec_cd(char *path, char *oldpwd)
{
	int	status;

	status = 0;
	if (ft_strcmp(path, "-") == 0)
		status = handle_dash(oldpwd);
	else if (ft_strcmp(path, "..") == 0)
		status = handle_dots(path);
	else
	{
		if (chdir(path) != 0)
			return (errno);
		set_path("OLDPWD", oldpwd);
	}
	if (status == 0)
		set_path("PWD", getcwd(NULL, 0));
	free(oldpwd);
	return (status);
}
