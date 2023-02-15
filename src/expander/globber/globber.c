/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:29:31 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/15 18:24:53 by fyuzhyk          ###   ########.fr       */
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
	while (argv[i] != NULL)
	{
		result = NULL;
		j = 0;
		while (argv[i][j] != '\0')
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
	char	*pattern;
	char	**result;

	result = NULL;
	pattern = find_pattern(arg, &(*index));
	result = check_for_path(pattern, result);
	if (ft_strcmp(pattern, "*/") != 0)
		result = get_matching_entries(NULL, pattern, result);
	return (result);
}
