/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:50:47 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/07 14:03:37 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // t_sym_tab
#include "libft.h" // ft_strncmp, ft_strlen
#include <stdio.h> // printf
#include <errno.h> // errno
#include <string.h> // strerror
#include <unistd.h> // chdir, getcwd

//@note ~ will be part of the general variable expansion

// include global var
extern		t_sym_tab **g_sym_table;

static void	set_var_value(char *var, char *value);
static void	handle_dots(void);
static void	handle_dash(void);

int	builtin_cd(char **argv)
{
	char		*pwd;
	char		*path;
	char		*oldpwd;
	t_sym_tab	*temp;

	if (argv[1] == NULL)
		return (errno);
	path = argv[1];
	oldpwd = getcwd(NULL, 0);
	if (ft_strncmp(path, "-", ft_strlen("-")) == 0)
		handle_dash();
	if (ft_strncmp(path, "..", ft_strlen("..")) == 0)
		handle_dots();
	else if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: %s\n", argv[1], strerror(errno));
		return (errno);
	}
	set_var_value("OLDPWD", oldpwd);
	pwd = getcwd(NULL, 0);
	set_var_value("PWD", pwd);
	return (errno);
}

static void	handle_dots(void)
{
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	i = ft_strlen(cwd) - 1;
	while (cwd[i] != '/' & i > 0)
	{
		cwd[i] = '\0';
		i--;
	}
	if (ft_strlen(cwd) > 1)
		cwd[i] = '\0';
	chdir(cwd);
}

static void	handle_dash(void)
{
	t_sym_tab	*temp;

	temp = *g_sym_table;
	while (temp)
	{
		if (ft_strncmp(temp->name, "OLDPWD", ft_strlen("OLDPWD")) == 0)
		{
			chdir(temp->value);
			printf("%s\n", temp->value);
			break ;
		}
		temp = temp->next;
	}
}

static void	set_var_value(char *var, char *value)
{
	t_sym_tab	*temp;

	temp = *g_sym_table;
	while (temp)
	{
		if (ft_strncmp(temp->name, var, ft_strlen(var)) == 0)
		{
			temp->value = value;
			return ;
		}
		temp = temp->next;
	}
}
