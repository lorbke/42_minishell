/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:38:45 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/23 13:23:13 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // NULL, ft_strlen, malloc
#include "../utils.h" // ft_realloc
#include "../expander.h" // expander_remove_quotes
#include "expander_private.h" // find_closing_quote, skip_quotes_in_quotes

void	quote_removal(char **argv)
{
	int	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i] != NULL)
	{
		expander_remove_quotes(argv[i]);
		i++;
	}
}

void	expander_remove_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			str[j] = str[i];
			j++;
		}
		else if (str[i] == '\'' || str[i] == '\"')
			skip_quotes_in_quotes(str, &i, &j);
		i++;
	}
	str[j] = '\0';
}
