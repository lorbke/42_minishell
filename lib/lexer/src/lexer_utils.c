/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:37:54 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/21 21:22:57 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h" // t_token, t_stack, TOK_* defines
#include "libft.h" // ft_strdup, ft_strchr
#include <stdlib.h> // malloc

int	is_special_char(char *str)
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
	else if (*str == '(' || *str == ')')
		return (1);
	return (0);
}

int	is_char_set(char c, char *seps)
{
	while (*seps)
	{
		if (*seps == c)
			return (1);
		seps++;
	}
	return (0);
}

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
	else if (ft_strchr(word, '\'')
		&& ft_strchr(word, '\"') > ft_strchr(word, '\'')
		&& ft_strchr(word, '\'') == ft_strrchr(word, '\''))
		return (TOK_UNCLOSED_SQUOTE);
	else if (ft_strchr(word, '\"')
		&& ft_strchr(word, '\"') == ft_strrchr(word, '\"'))
		return (TOK_UNCLOSED_DQUOTE);
	else if (*word == '(')
		return (TOK_SUBSHELL);
	else if (*word == '&' && *(word + 1) == '&')
		return (TOK_AND);
	else if (*word == '|' && *(word + 1) == '|')
		return (TOK_OR);
	return (TOK_WORD);
}

t_token	*create_token(char *word, int len)
{
	t_token	*new;

	if (!word || !*word)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = ft_strdup(word);
	new->word[len] = 0;
	new->desc = desc_word(word);
	return (new);
}

t_stack	*create_stack_node(t_token *token)
{
	t_stack	*new;

	if (!token)
		return (NULL);
	new = malloc(sizeof(t_stack));
	new->token = token;
	new->next = NULL;
	return (new);
}
