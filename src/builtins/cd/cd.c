/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:50:47 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/08 11:52:59 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // t_sym_tab
#include "libft.h" // ft_strncmp, ft_strlen
#include "cd_private.h" // set_path, get_path, check_prev_dir, check_for_dots
#include <stdio.h> // printf
#include <errno.h> // errno
#include <string.h> // strerror
#include <unistd.h> // chdir, getcwd

//@note ~ will be part of the general variable expansion

static void	handle_dash(char *oldpwd);
static void	handle_dots(char *path);

int	builtin_cd(char **argv)
{
	char		*path;
	char		*oldpwd;
	t_sym_tab	*temp;

	if (argv[1] == NULL)
		return (errno);
	path = argv[1];
	oldpwd = getcwd(NULL, 0);
	if (ft_strncmp(path, "-", ft_strlen("-")) == 0)
		handle_dash(oldpwd);
	else if (ft_strncmp(path, "..", ft_strlen("..")) == 0)
		handle_dots(argv[1]);
	else
	{
		if (chdir(path) != 0)
		{
			perror(ft_strjoin("minishell: cd: ", argv[1]));
			return (errno);
		}
		set_path("OLDPWD", oldpwd);
	}
	set_path("PWD", getcwd(NULL, 0));
	return (errno);
}

static void	handle_dash(char *oldpwd)
{
	t_sym_tab	*temp;
	char		*path;

	temp = *g_sym_table;
	while (temp)
	{
		if (ft_strncmp(temp->var, "OLDPWD", ft_strlen("OLDPWD")) == 0)
		{
			path = get_path(temp->var);
			if (path == NULL)
				break ;
			if (chdir(path) != 0)
			{
				perror(ft_strjoin("minishell: cd: ", path));
				return ;
			}
			set_path("OLDPWD", oldpwd);
			printf("%s\n", path);
			return ;
		}
		temp = temp->next;
	}
	ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
}

static void	handle_dots(char *path)
{
	int		i;
	int		count;
	char 	*start;

	i = 0;
	start = getcwd(NULL, 0);
	set_path("OLDPWD", getcwd(NULL, 0));
	count = check_for_dots(path, &i);
	while (count)
	{
		change_prev_dir();
		count--;
	}
	if (ft_strlen(path) > i)
	{
		if (chdir(&path[i]) != 0)
		{
			chdir(start);
			perror(ft_strjoin("minishell: cd: ", path));
		}
	}
}