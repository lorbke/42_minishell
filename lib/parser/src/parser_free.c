/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:56:21 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 20:47:33 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include <stdlib.h> // free

/**
 * It frees a token
 * 
 * @param token The token to free.
 * 
 * @return A pointer to a t_token struct.
 */
static void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->word)
		free(token->word);
	free(token);
}

/**
 * It frees the memory allocated for the ast
 * 
 * @param ast_void The ast to free.
 * 
 * @return A pointer to a t_ast structure.
 */
void	parser_free_ast(void *ast_void)
{
	t_ast	*ast;

	ast = (t_ast *)ast_void;
	if (ast == NULL)
		return ;
	parser_free_ast(ast->left);
	parser_free_ast(ast->right);
	free_token(ast->token);
	free(ast);
}
