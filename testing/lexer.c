/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/16 20:01:11 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// quotes single tokens or big token?
// merge identification and insertion?
// backlink to parent node for the ast?
/* LR ascend parser

	1. get token from input stack
	2. identify token
	3. if precedence lower than current token, append based on current token type
	4. if precedence higher than current token, return up the stack until precedence is lower

	- how to handle left and right appending?
		-> left and right part of recursive function

	pseudo code:
		fn asdf(token)
			next_token = asdf(next_token)
			if (asdf(next_token)->presc > token->presc)
				return ()
			else
				token->right = asdf(next_token)

		fn basdf(word)
			token = create_token(word)
			if (token->word)
				token->a = basdf(strsep)
*/

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

t_token	*create_token(char *word)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->word = word;
	new->desc = 100;
	return (new);
}

unsigned int	desc_word(char *word)
{
	if (*word == '|')
		return (2);
	if (*word != '\0')
		return (1);
	return (0);
}

void	print_ast(t_token *head)
{
	while (head)
	{
		printf("%s->", head->word);
		head = head->a;
	}
}

t_token	*parse_recursive(char *word, unsigned int desc, char *input, char *sep)
{
	t_token	*token;
	t_token	*next;

	token = NULL;
	if (word)
	{
		token = create_token(word);
		token->desc = desc_word(word);
		if (token->desc > desc)
			return (token);
		next = parse_recursive(ft_strsep(&input, sep), token->desc, input, sep);
		token->a = next;
	}
	return (token);
}

int	main(void)
{
	char	*input;
	char	*seps = " \t\n\r";
	t_token	*head;

	input = malloc(100);
	strcpy(input, "ls	-l -a |\necho\rhello");
	head = create_token("[HEAD]");
	head->a = parse_recursive(ft_strsep(&input, seps), 0, input, seps);
	print_ast(head);
	return (0);
}
