/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:38:45 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/10 08:58:38 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlen, malloc
#include "expander_private.h" // ft_realloc

static int	find_closing_quote(char *str, int *index);

void	quote_removal(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

// @note needs to be tested if quotes are implemented in parser
char*	handle_single_quotes(char *result, char *str, int *index, int *result_index)
{
	int		i;
	int		str_len;
	char	*arg;

	(*index)++;
	str_len = find_closing_quote(str, &(*index));
	if (!result)
		arg = malloc(sizeof(char) * str_len + 1);
	else
		arg = ft_realloc(result, ft_strlen(result) + str_len);
	i = 0;
	while (i < str_len)
	{
		arg[i] = str[i];
		i++;
		(*result_index)++;
	}
	return (arg);
}

static int	find_closing_quote(char *str, int *index)
{
	int	str_len;

	str_len = 1;
	while (str[str_len])
	{
		if (str[str_len] == '\'')
		{
			(*index)++;
			break ;
		}
		str_len++;
		(*index)++;
	}
	return (str_len);
}
