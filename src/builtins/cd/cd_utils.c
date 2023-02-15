/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:43:00 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/15 13:22:26 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // t_sym_tab
#include "libft.h" // ft_strncmp, ft_strlen, ft_strdup, ft_strjoin
#include "../../utils.h" // ft_strcmp

int	check_for_dots(char *path, int *i)
{
	int	count;

	count = 0;
	while (ft_strcmp(&path[*i], "..") == 0)
	{
		count++;
		*i += 3;
	}
	return (count);
}

void	change_prev_dir(void)
{
	int		i;
	char	*cwd;

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

char	*get_path(char *var)
{
	char	**split;

	split = ft_split(var, '=');
	if (split[1] == NULL)
		return (NULL);
	else
		return (split[1]);
}

void	set_path(char *var, char *value)
{
	t_sym_tab	*temp;
	char		*path;

	temp = *g_sym_table;
	while (temp)
	{
		if (ft_strncmp(temp->var, var, ft_strlen(var)) == 0)
		{
			temp->var = ft_strjoin(var, "=");
			temp->var = ft_strjoin(temp->var, value);
			return ;
		}
		temp = temp->next;
	}
	if (value)
	{
		path = ft_strjoin(var, "=");
		path = ft_strjoin(path, value);
		add_to_back(g_sym_table, new_sym_tab_node(path));
	}
}
