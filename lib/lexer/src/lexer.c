/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:04:01 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/22 17:45:04 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_lexer.h" // main header
#include "lexer.h" // TOK_* macros, t_token, t_stack
#include "libft.h" // ft_strchr
#include <stdlib.h> // NULL
#include <unistd.h> // free
#include <stdio.h> // printf

static int	is_special_char(char *str)
{
	if (*str == '<' && *(str + 1) == '<')
		return (2);
	else if (*str == '>' && *(str + 1) == '>')
		return (2);
	else if (*str == '<')
		return (1);
	else if (*str == '>')
		return (1);
	else if (*str == '|' && *(str + 1) == '|')
		return (2);
	else if (*str == '|')
		return (1);
	else if (*str == '&' && *(str + 1) == '&')
		return (2);
	else if (*str == '&')
		return (1);
	else if (*str == ')')
		return (1);
	return (0);
}

static char	*skip_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			str = skip_until_after_char(str + 1, *str);
		else if (ft_isspace(*str) || is_special_char(str))
			break ;
		else if (*str == '(')
			break ;
		else if (*str)
			str++;
	}
	return (str);
}

static char	*skip_subshell(char *str)
{
	int		depth;

	depth = 1;
	str++;
	while (*str && depth)
	{
		if (*str == '(')
			depth++;
		else if (*str == ')')
			depth--;
		str++;
	}
	return (str);
}

static char	*get_next_word(char **str)
{
	char	*temp;
	int		special;

	while (ft_isspace(**str))
		(*str)++;
	special = is_special_char(*str);
	temp = *str;
	if (special)
	{
		*str += special;
		return (ft_strdup_size(temp, special + 1));
	}
	if (**str == '(')
		*str = skip_subshell(*str);
	else
		*str = skip_quotes(*str);
	return (ft_strdup_size(temp, *str - temp + 1));
}

t_stack	*lexer_str_to_tokstack(char *str)
{
	t_stack	*head;
	t_stack	*temp;
	char	*word;

	word = get_next_word(&str);
	head = create_stack_node(create_token(word));
	if (!head)
		return (NULL);
	temp = head;
	while (*str)
	{
		word = get_next_word(&str);
		temp->next = create_stack_node(create_token(word));
		if (!temp->next)
			break ;
		temp = temp->next;
	}
	return (head);
}
