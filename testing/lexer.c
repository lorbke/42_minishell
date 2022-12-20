/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/20 19:39:32 by lorbke           ###   ########.fr       */
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
	new->a = NULL;
	new->b = NULL;
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

void	simple_print_ast(t_token *head)
{
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
}

void	print_ast(t_token *head)
{
	t_token	*temp;
	int		width_a;
	int		width_b;

	temp = create_token(NULL);
	width_a = 60;
	width_b = 5;
	printf("\n");
	// while (head)
	// {
	// 	if (head && head->word)
	// 		printf("%*s", width_a, head->word);
	// 	if (temp && temp->word)
	// 		printf("%*s", width_b, temp->word);
	// 	printf("\n");
	// 	temp = head->b;
	// 	head = head->a;
	// 	width_a -= 5;
	// 	width_b += 5;
	// }
	printf("\n");
}

// t_token	*parse_recursive(char *input, char *seps)
// {
// 	t_token	*token;
// 	t_token	*next;
// 	t_token	*temp;

// 	token = create_token(ft_strsep(&input, seps));
// 	if (!token->word)
// 		return (NULL);
// 	token->desc = desc_word(token->word);
// 	next = parse_recursive(input, seps);
// 	if (next && next->desc > token->desc)
// 	{
// 		token->a = next->a;
// 		next->a = token;
// 		return (next);
// 	}
// 	if (token->a)
// 		token->b = next;
// 	else
// 		token->a = next;
// 	return (token);
// }

// t_token	*parse_recursive(t_token *head, char *input, char *seps)
// {
// 	t_token	*token;
// 	t_token	*next;
// 	t_token	*temp;

// 	token = create_token(ft_strsep(&input, seps));
// 	if (!token->word)
// 		return (NULL);
// 	token->desc = desc_word(token->word);
// 	next = parse_recursive(head, input, seps);
// 	while (head)
// 	{
// 		if (token->desc > head->desc)
// 		{
// 			token->a = head->a;
// 			temp->a = token;
// 		}
// 		temp = head;
// 		head = head->a;
// 	}
// 	return (NULL);
// }

t_token	*parse_recursive(t_token *previous, char *input, char *seps)
{
	t_token	*token;
	t_token	*temp;

	token = create_token(ft_strsep(&input, seps));
	if (!token->word)
		return (NULL);
	token->desc = desc_word(token->word);
	previous->a = token;
	temp = parse_recursive(token, input, seps);
	if (!temp)
		return (token);
	if (temp && temp->desc <= previous->desc)
	{
		previous->a = temp;
		temp->a = token;
	}
	else
		return (temp);
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
	parse_recursive(head, input, seps);
	simple_print_ast(head);
	// print_ast(head);
	return (0);
}
