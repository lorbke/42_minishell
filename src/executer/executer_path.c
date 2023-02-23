/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:44:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/23 19:19:15 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlen, ft_strncmp, ft_strjoin
#include "garbage_collector.h" // gc_free_* functions
#include <sys/stat.h> // stat, S_ISDIR, S_ISREG


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
	// @note protected
	if (path_set == NULL)
		return (NULL);
	path_set = ft_strtrim(path_set, PATH_ENV);
	return (path_set);
}

#include <stdio.h>

char	*get_cmd_path(char **env, char *cmd)
{
	char	*path_str;
	char	**path_arr;
	char	**temp_arr;
	char	*temp;
	struct stat s;

	path_str = get_pathset(env);
	// @note protected
	if (path_str == NULL)
		return (NULL);
	cmd = ft_strjoin("/", cmd);
	path_arr = ft_split(path_str, ':');
	temp_arr = path_arr;
	free(path_str);
	while (*path_arr)
	{
		temp = ft_strjoin(*path_arr, cmd);
		// printf("temp: %s\n", temp);
		// printf("access: %d\n", access(temp, X_OK | F_OK));
		// printf("stat: %d\n", stat(temp, &s));
		// printf("S_ISDIR: %d\n", S_ISDIR(s.st_mode));
		// printf("S_ISREG: %d\n", S_ISREG(s.st_mode));
		if (access(temp, F_OK) == 0 && (!stat(temp, &s) && !S_ISDIR(s.st_mode)))
		{
			free(cmd);
			gc_free_str_arr(temp_arr);
			return (temp);
		}
		free(temp);
		path_arr++;
	}
	free(cmd);
	gc_free_str_arr(temp_arr);
	return (NULL);
}
