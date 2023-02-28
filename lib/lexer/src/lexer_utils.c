/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:37:54 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:17:00 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h" // t_token, t_stack, TOK_* defines
#include "libft.h" // ft_strdup, ft_strchr
#include <stdlib.h> // malloc

/**
 * It returns a pointer to the first character after the first occurrence of 
 * the character c in the string str
 * 
 * @param str The string to search through.
 * @param c The character to skip until after.
 * 
 * @return A pointer to the first character after the first occurence of 
 * c in str.
 */
char	*skip_until_after_char(char *str, char c)
{
	while (*str && *str != c)
		str++;
	if (*str)
		str++;
	return (str);
}

/**
 * It checks if there's an unclosed quote in a string
 * 
 * @param str The string to check.
 * 
 * @return The function is_unclosed_quote() returns the type of quote 
 * that is unclosed.
 */
static int	is_unclosed_quote(char *str)
{
	char	quote;

	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str;
			str++;
			while (*str && *str != quote)
				str++;
			if (!*str && quote == '\'')
				return (1);
			else if (!*str && quote == '\"')
				return (2);
			else
				str++;
		}
		else
			str++;
	}
	return (0);
}

/**
 * It returns the type of token that the given word is
 * 
 * @param word the word to be described
 * 
 * @return the type of token that is being passed in.
 */
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
	else if (*word == '(' || *word == ')')
		return (TOK_SUBSHELL);
	else if (*word == '&' && *(word + 1) == '&')
		return (TOK_AND);
	else if (*word == '|' && *(word + 1) == '|')
		return (TOK_OR);
	else if (ft_strchr(word, '\'') || ft_strchr(word, '\"'))
		return (TOK_QUOTED);
	return (TOK_WORD);
}

/**
 * It creates a new token
 * 
 * @param word The word to be tokenized.
 * 
 * @return A pointer to a t_token struct.
 */
t_token	*create_token(char *word)
{
	t_token	*new;

	if (!word || !*word)
		return (NULL);
	new = ft_malloc_safe(sizeof(t_token), 1);
	new->word = word;
	new->desc = desc_word(word);
	return (new);
}

/**
 * It creates a new stack node
 * and returns a pointer to it
 * 
 * @param token The token to be added to the stack.
 * 
 * @return A pointer to a t_stack struct.
 */
t_stack	*create_stack_node(t_token *token)
{
	t_stack	*new;

	if (!token)
		return (NULL);
	new = ft_malloc_safe(sizeof(t_stack), 1);
	new->token = token;
	new->next = NULL;
	return (new);
}
