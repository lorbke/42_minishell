/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/15 20:00:37 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// quotes single tokens or big token?
// merge identification and insertion?

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

char	*ft_strsep(char **stringp, const char *delim);

typedef struct s_token
{
	char			*word;
	unsigned int	desc;
	void			*a;
	void			*b;
}	t_token;

t_token	*create_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->word = NULL;
	new->desc = 0;
	return (new);
}

unsigned int	desc_word(char *word)
{
	if (word[0] != '\0')
		return (1);
	if (word[0] == '|')
		return (2);
	return (0);
}

t_token	*insert_node(t_token *current, t_token *next)
{
	if (next->desc == 1)
	{
		current->a = next;
		return (next);
	}
	else if (next->desc == 2)
	{
		next->a = current;
		return (next);
	}
	else
	{
		free(next);
		return (current);
	}
}

void	print_ast(t_token *head)
{
	while (head)
	{
		printf("%s->", head->word);
		head = head->a;
	}
}

void	parse_input(char *input)
{
	char	*seps = " \t\n\r";
	t_token	*head;
	t_token	*current;
	t_token	*next;

	head = malloc(sizeof(t_token));
	current = head;
	while (input)
	{
		next = create_token();
		next->word = ft_strsep(&input, seps);
		next->desc = desc_word(next->word);
		current = insert_node(current, next);
	}
	print_ast(head);
}

int	main(void)
{
	char	*test;

	test = malloc(100);
	strcpy(test, "ls -l -a | echo hello");
	parse_input(test);
	return 0;
}
