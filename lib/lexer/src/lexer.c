/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:04:01 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/22 14:11:49 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_lexer.h" // main header
#include "lexer.h" // TOK_* macros, t_token, t_stack
#include "libft.h" // ft_strchr
#include <stdlib.h> // NULL
#include <unistd.h> // free
#include <stdio.h> // printf

static int	ignore_delims(char *stringp, const char *ignore)
{
	char	*esc;
	char	*start;
	int		count;

	if (stringp + 1 && *(stringp + 1) == '(')
		return (1);
	start = stringp;
	esc = ft_strchr(ignore, *start);
	if (esc && *esc == '(')
		esc++;
	if (esc)
	{
		if (*esc == '\"' || *esc == '\'')
		{
			count = 0;
			while (*start)
			{
				if (*start == *esc)
					count++;
				start++;
			}
			start = stringp;
			while (*start && count > 0)
			{
				if (*start == *esc)
					count--;
				start++;
			}
			if (*start == *esc)
				start++;
			while (*start && ft_isalpha(*start))
				start++;
		}
		return (start - stringp);
	}
	return (0);
}

static int	get_word_len(char *word, char *esc)
{
	int	len;
	int	ignore;
	int	special;

	len = 0;
	while (word && word[len])
	{
		ignore = ignore_delims(word + len, esc);
		if (ignore)
			return (len + ignore);
		special = is_special_char(word + len);
		if (special)
		{
			if (!len)
				return (special);
			else
				return (len);
		}
		len++;
	}
	return (len);
}

static char	*get_next_word(char **str, char *seps, char *esc)
{
	static char	*word = NULL;

	if (!str)
		word = NULL;
	else if (word && *word)
		word += get_word_len(word, esc);
	else
	{
		word = lexer_ft_strsep(str, seps, esc);
	}
	return (word);
}

t_stack	*lexer_str_to_tokstack(char *str, char *seps, char *esc)
{
	t_stack	*head;
	t_stack	*temp;
	char	*next_word;
	char	*temp_str;

	str = ft_strdup(str);
	temp_str = str;
	while (*str && is_char_set(*str, seps))
		str++;
	next_word = get_next_word(&str, seps, esc);
	head = create_stack_node
		(create_token(next_word, get_word_len(next_word, esc)));
	if (!head && !get_next_word(NULL, NULL, NULL))
	{
		free(temp_str);
		return (NULL);
	}
	temp = head;
	while ((str && *str) || next_word)
	{
		next_word = get_next_word(&str, seps, esc);
		temp->next = create_stack_node
			(create_token(next_word, get_word_len(next_word, esc)));
		if (temp->next)
			temp = temp->next;
	}
	temp->next = NULL;
	get_next_word(NULL, NULL, NULL);
	free(temp_str);
	return (head);
}
