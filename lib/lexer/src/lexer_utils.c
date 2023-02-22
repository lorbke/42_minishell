/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:37:54 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/22 17:53:19 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h" // t_token, t_stack, TOK_* defines
#include "libft.h" // ft_strdup, ft_strchr
#include <stdlib.h> // malloc

char	*skip_until_after_char(char *str, char c)
{
	while (*str && *str != c)
		str++;
	if (*str)
		str++;
	return (str);
}

static int	is_unclosed_quote(char *str)
{
	char	quote;

	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str;
			str = skip_until_after_char(str + 1, *str);
			if (!*str && *(str - 1) != quote)
			{
				if (quote == '\'')
					return (1);
				else if (quote == '\"')
					return (2);
			}
		}
		else
			str++;
	}
	return (0);
}

// @todo unclosed quote handling is broken
unsigned char	desc_word(char *word)
{
	if (*word == '|' && *(word + 1) != '|')
		return (TOK_PIPE);
	else if (*word == '<' && *(word + 1) == '<')
		return (TOK_REDIR_HEREDOC);
	else if (*word == '>' && *(word + 1) == '>')
		return (TOK_REDIR_APPEND);
	else if (*word == '<')
		return (TOK_REDIR_IN);
	else if (*word == '>')
		return (TOK_REDIR_OUT);
	else if (is_unclosed_quote(word) == 1)
		return (TOK_UNCLOSED_SQUOTE);
	else if ((is_unclosed_quote(word) == 2))
		return (TOK_UNCLOSED_DQUOTE);
	else if (*word == '(')
		return (TOK_SUBSHELL);
	else if (*word == '&' && *(word + 1) == '&')
		return (TOK_AND);
	else if (*word == '|' && *(word + 1) == '|')
		return (TOK_OR);
	return (TOK_WORD);
}

t_token	*create_token(char *word)
{
	t_token	*new;

	if (!word || !*word)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(word);
		return (NULL);
	}
	new->word = word;
	new->desc = desc_word(word);
	return (new);
}

t_stack	*create_stack_node(t_token *token)
{
	t_stack	*new;

	if (!token)
		return (NULL);
	new = malloc(sizeof(t_stack));
	if (!new)
	{
		free(token);
		return (NULL);
	}
	new->token = token;
	new->next = NULL;
	return (new);
}
