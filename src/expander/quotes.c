/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:38:45 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/13 13:28:54 by fyuzhyk          ###   ########.fr       */
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
	while (argv[i])
	{
		remove_quotes(argv[i]);
		i++;
	}
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
		arg = ft_realloc(result, ft_strlen(result) + str_len + 1);
	i = 0;
	while (i < str_len)
	{
		// @note result_index or i as index for arg?
		arg[*result_index] = str[i];
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

static void	remove_quotes(char *str)
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
