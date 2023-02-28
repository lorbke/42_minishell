/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exec_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:44:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:31:24 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlen, ft_strncmp, ft_strjoin
#include "garbage_collector.h" // gc_free_* functions
#include <sys/stat.h> // stat, S_ISDIR, S_ISREG

#define PATH_ENV "PATH="

/**
 * It searches for a string in an array of strings
 * 
 * @param str_arr a NULL terminated array of strings
 * @param needle the string to search for
 * 
 * @return A pointer to the first occurrence of the string needle 
 * in the string haystack, or a null
 * pointer if needle is not part of haystack.
 */
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

/**
 * It takes an environment
 * variable array and returns a string containing the PATH environment variable
 * 
 * @param env the environment variables
 * 
 * @return The pathset is being returned.
 */
static char	*get_pathset(char **env)
{
	char	*path_set;

	path_set = ft_strnstr_arr(env, PATH_ENV);
	if (path_set == NULL)
		return (NULL);
	path_set = ft_strtrim(path_set, PATH_ENV);
	if (!path_set)
		ft_perror_and_exit("executer: ft_strtrim: malloc: ");
	return (path_set);
}

/**
 * It takes a list of paths and a command name, and returns the first 
 * path that contains a valid
 * executable file with the given name.
 * 
 * @param path_arr an array of strings, each string is a path to a directory
 * @param cmd the command to be executed
 * 
 * @return A string that is the path to the command.
 */
static char	*get_valid_cmd_str(char **path_arr, char *cmd)
{
	char		*temp_str;
	char		**temp_arr;
	struct stat	file_stats;

	temp_arr = path_arr;
	while (*temp_arr)
	{
		temp_str = ft_strjoin(*temp_arr, cmd);
		if (!temp_str)
			ft_perror_and_exit("executer: ft_strjoin: malloc: ");
		if (access(temp_str, X_OK) == 0
			&& (!stat(temp_str, &file_stats)
				&& !S_ISDIR(file_stats.st_mode)))
			return (temp_str);
		free(temp_str);
		temp_arr++;
	}
	return (NULL);
}

/**
 * It takes a command name and an environment, and returns 
 * the full path to the command if it exists, or NULL if it doesn't
 * 
 * @param env The environment variables.
 * @param cmd the command to be executed
 * 
 * @return A string containing the path to the command to be executed.
 */
char	*exec_get_cmd_path(char **env, char *cmd)
{
	char		*path_str;
	char		**path_arr;
	char		*valid_cmd;

	path_str = get_pathset(env);
	if (path_str == NULL)
	{
		valid_cmd = ft_strdup(cmd);
		if (!valid_cmd)
			ft_perror_and_exit("executer: ft_strdup: malloc: ");
		return (valid_cmd);
	}
	path_arr = ft_split(path_str, ':');
	free(path_str);
	if (!path_arr)
		ft_perror_and_exit("executer: ft_split: malloc: ");
	cmd = ft_strjoin("/", cmd);
	if (!cmd)
		ft_perror_and_exit("executer: ft_strjoin: malloc: ");
	valid_cmd = get_valid_cmd_str(path_arr, cmd);
	free(cmd);
	gc_free_str_arr(path_arr);
	return (valid_cmd);
}
