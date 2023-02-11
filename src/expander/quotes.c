/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:38:45 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/10 19:19:08 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlen, malloc
#include "expander_private.h" // ft_realloc

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
char*	handle_quotes(char *result, char *str, int *index, int *result_index)
{
	int		i;
	int		str_len;
	char	*arg;
	char	quote_type;

	quote_type = str[(*index)++];
	str_len = find_closing_quote(str, &(*index), quote_type);
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

// @note I think this way the func also recognizes if the closing quote
// directly follows the opening quote ?
int	find_closing_quote(char *str, int *index, char quote_type)
{
	int	str_len;

	str_len = 1;
	while (str[str_len])
	{
		if (str[str_len] == quote_type)
		{
			(*index)++;
			break ;
		}
		str_len++;
		(*index)++;
	}
	return (str_len);
}
