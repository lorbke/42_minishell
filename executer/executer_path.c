
#include "libft.h"

#define PATH_ENV "PATH="

static char	*ft_strnstr_arr(char **str_arr, char *needle)
{
	while (*str_arr)
	{
		if (ft_strnstr(*str_arr, needle, ft_strlen(*str_arr)) != NULL)
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
