/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:50:47 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 19:19:34 by lorbke           ###   ########.fr       */
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
