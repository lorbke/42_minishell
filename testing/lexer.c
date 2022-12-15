/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/15 15:16:04 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/libft/includes/libft.h"

// quotes single tokens or big token?

// 1. get next token
// 2. quote identifier
// 	- if token contains quote, get next token until quote is closed
// 	- lots of quote edge cases
// 3. check for other special characters
// 	- heredoc
// 	- redirection and append
// 	- pipe
// 	- operator
// 	- word
// 4. insert node into AST
// (5. check for syntax errors)
// 6. repeat until EOF

typedef struct s_token
{
	char			*token;
	unsigned int	desc;
	void			*a;
	void			*b;
}	t_token;

void	add_token(t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	token->a = new;
}

int	main(void)
{
	char	*sep = "\\/:;=-";
	char	*test;
	t_token	*head;
	t_token	*current;

	test = malloc(100);
	strcpy(test, "This\\is:a;test-string==");
	head = malloc(sizeof(t_token));
	current = head;
	while (test)
	{
		add_token(current);
		current = current->a;
		current->token = ft_strsep(&test, sep);
	}
	while (head)
	{
		printf("%s->", head->token);
		head = head->a;
	}
	return 0;
}
