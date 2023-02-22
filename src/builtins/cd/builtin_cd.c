/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:50:47 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/21 19:34:43 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // t_sym_tab
#include "libft.h" // ft_strncmp, ft_strlen
#include "cd_private.h" // handle_dash, handle_dots, set_path
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
	if (argv[1] == NULL)
		return (status);
	path = argv[1];
	oldpwd = getcwd(NULL, 0);
	status = exec_cd(path, oldpwd);
	return (status);
}

static int	exec_cd(char *path, char *oldpwd)
{
	int	status;

	if (oldpwd == NULL)
		return (errno);
	if (ft_strcmp(path, "-") == 0)
		status = handle_dash(oldpwd);
	else if (ft_strcmp(path, "..") == 0)
		status = handle_dots(path);
	else
	{
		if (chdir(path) != 0)
		{
			ft_perror("cd", path);
			return (errno);
		}
		set_path("OLDPWD", oldpwd);
	}
	set_path("PWD", getcwd(NULL, 0));
	free(oldpwd);
	return (status);
}
