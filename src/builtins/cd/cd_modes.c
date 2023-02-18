/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_modes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:48:10 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/18 14:32:21 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // t_sym_tab
#include "libft.h" // free, ft_strncmp, ft_strlen, ft_putstr_fd
#include "../../utils.h" // ft_perror
#include "cd_private.h" // check_for_dots, set_path, get_path
#include <errno.h> // errno
#include <unistd.h> // chdir, getcwd
#include <stdio.h> // perror

static int	cd_oldpwd(char *var, char  *oldpwd);
static int	cd_back(int count, int i, char *path, char *cwd);

int	handle_dash(char *oldpwd)
{
	t_sym_tab	*temp;
	int			status;

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
	// ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
	ft_perror("cd", "OLDPWD not set");
	return (1);
}

int	handle_dots(char *path)
{
	int		i;
	int		count;
	int		status;
	char 	*cwd;

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

static int	cd_oldpwd(char *var, char  *oldpwd)
{
	char	*path;

	path = get_path(var);
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
	if (ft_strlen(path) > i)
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
