/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:38:45 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 20:33:31 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // NULL, ft_strlen, malloc
#include "../../utils.h" // utils_ft_realloc
#include "../../quotes.h" // quotes_rmv_quotes_from_str,
// quotes_find_closing_quote, skip_quotes_in_quotes

void	quote_removal(char **argv)
{
	int	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i] != NULL)
	{
		quotes_rmv_quotes_from_str(argv[i]);
		i++;
	}
}

void	quotes_rmv_quotes_from_str(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\'' && str[i] != '"')
		{
			str[j] = str[i];
			j++;
		}
		else if (str[i] == '\'' || str[i] == '"')
		{
			if (ft_strchr(&str[i + 1], str[i]) != NULL)
			{
				skip_quotes_in_quotes(str, &i, &j);
				if (str[i] == '\0')
					break ;
			}
		}
		i++;
	}
	str[j] = '\0';
}
