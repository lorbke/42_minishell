/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:04:01 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/14 17:47:08 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// where to handle token specific errors like only one &, unnmatched quotes, etc.?
static int	desc_word(char *word)
{
	if (*word == '|')
		return (TOKEN_PIPE);
	else if (*word == '<')
		return (TOKEN_REDIR_IN);
	else if (*word == '>')
		return (TOKEN_REDIR_OUT);
	else if (*word == '\'')
		return (TOKEN_SQUOTE);
	else if (*word == '"')
		return (TOKEN_DQUOTE);
	else if (*word == '(')
		return (TOKEN_SUBSHELL);
	else if (*word == '&' && *(word + 1) == '&')
		return (TOKEN_AND);
	else if (*word == '|' && *(word + 1) == '|')
		return (TOKEN_OR);
	return (TOKEN_WORD);
}

static t_token	*create_token(char *word)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->word = word;
	if (word)
		new->desc = desc_word(word);
	return (new);
}

static t_stack	*create_list_node(t_token *token)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	new->token = token;
	new->next = NULL;
	return (new);
}

t_stack	*str_to_tokstack(char *str, char *seps)
{
	t_stack	*head;
	t_stack	*temp;

	if (!*str || !str)
		return (NULL);
	head = create_list_node(create_token(ft_strsep(&str, seps)));
	temp = head;
	while (*str)
	{
		temp->next = create_list_node(create_token(ft_strsep(&str, seps)));
		temp = temp->next;
	}
	temp->next = NULL;
	return (head);
}
