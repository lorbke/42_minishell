/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:29:31 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/13 13:30:11 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // NULL
#include "globber.h" // globbing, is_match, concatentate_entries, add_matching_entries, find_pattern, opendir, readdir, closedir
#include "../expander_private.h" // find_closing_quote, quote_removal

static char	**globbing(char *arg, int *index);

char	**globber(char **argv)
{
	int		i;
	int		j;
	char	**result;
	char	**expanded_argv;

	i = 1;
	expanded_argv = NULL;
	while (argv[i])
	{
		result = NULL;
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '\'' || argv[i][j] == '\"')
				find_closing_quote(argv[i], &j, argv[i][j]);
			else if (argv[i][j] == '*')
				result = globbing(argv[i], &j);
			j++;
		}
		expanded_argv = add_vars(expanded_argv, result, &argv[i]);
		i++;
	}
	expanded_argv = create_new_cmd(expanded_argv, argv);
	quote_removal(expanded_argv);
	return (expanded_argv);
}

static char **globbing(char *arg, int *index)
{
	char			*pwd;
	char			*pattern;
	char			**result;
	DIR				*dir;
	struct dirent	*entry;

	result = NULL;
	pwd = getcwd(NULL, 0);
	pattern = find_pattern(arg, &(*index));
	dir = opendir(pwd);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] != '.' || ft_strcmp(pattern, ".*") == 0)
		{
			if (is_match(entry->d_name, pattern))
				result = add_matching_entry(result, entry->d_name);
		}
	}
	closedir(dir);
	free(pattern);
	return (result);
}
