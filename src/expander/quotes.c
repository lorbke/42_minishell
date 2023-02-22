/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:38:45 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/22 22:23:48 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // NULL, ft_strlen, malloc
#include "../utils.h" // ft_realloc
#include "expander_private.h" // find_closing_quote

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
	i = *index;
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
			break ;
		str_len++;
		(*index)++;
	}
	return (str_len);
}

int	in_closed_quotes(char *result, char *arg, int *index, int *result_index)
{
	int	i;
	int	quote_count;

	i = *index;
	quote_count = 0;
	if (arg[*index + 1] == '"' || arg[*index + 1] == '\'')
	{
		while (arg[i] != '\0')
		{
			if (arg[i] == '"' || arg[i] == '\'')
				quote_count++;
			i++;
		}
		if (quote_count % 2 != 0)
			return (1);
	}
	return (0);
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
