/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:38:45 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/17 13:20:05 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlen, malloc
#include "expander_private.h" // ft_realloc

static void	remove_quotes(char *str);

void	quote_removal(char **argv)
{
	int	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i] != NULL)
	{
		remove_quotes(argv[i]);
		i++;
	}
}

char	*handle_quotes(char *result, char *str, int *index, int *result_index)
{
	int		i;
	int		str_len;
	char	*arg;
	char	quote_type;

	quote_type = str[(*index)];
	i = *index + 1;
	str_len = find_closing_quote(str, &(*index), quote_type);
	if (result == NULL)
	{
		arg = malloc(sizeof(char) * str_len + 1);
		if (arg == NULL)
			return (NULL);
	}
	else
		arg = ft_realloc(result, ft_strlen(result) + str_len + 1);
	while (i < *index)
	{
		arg[*result_index] = str[i];
		i++;
		(*result_index)++;
	}
	arg[*result_index] = '\0';
	return (arg);
}

int	find_closing_quote(char *str, int *index, char quote_type)
{
	int	str_len;

	str_len = 0;
	(*index)++;
	while (str[*index] != '\0')
	{
		if (str[*index] == quote_type)
		{
			(*index)++;
			break ;
		}
		str_len++;
		(*index)++;
	}
	return (str_len);
}

static void	remove_quotes(char *str)
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
		i++;
	}
	str[j] = '\0';
}
