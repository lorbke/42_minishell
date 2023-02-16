/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:44:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/16 14:44:55 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define PATH_ENV "PATH="

static char	*ft_strnstr_arr(char **str_arr, char *needle)
{
	int	needle_len;

	needle_len = ft_strlen(needle);
	while (*str_arr)
	{
		if (ft_strncmp(*str_arr, needle, needle_len) == 0)
			return (*str_arr);
		str_arr++;
	}
	return (NULL);
}

static char	*get_pathset(char **envp)
{
	char	*path_set;

	path_set = ft_strnstr_arr(envp, PATH_ENV);
	path_set = ft_strtrim(path_set, PATH_ENV);
	return (path_set);
}

char	*get_cmd_path(char **env, char *cmd)
{
	char	*path_str;
	char	**path_arr;
	char	*temp;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_str = get_pathset(env);
	cmd = ft_strjoin("/", cmd);
	path_arr = ft_split(path_str, ':');
	while (*path_arr)
	{
		temp = ft_strjoin(*path_arr, cmd);
		if (access(temp, X_OK) == 0)
		{
			free(path_str);
			return (temp);
		}
		free(temp);
		path_arr++;
	}
	return (NULL);
}
