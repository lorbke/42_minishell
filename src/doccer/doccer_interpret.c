/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_interpret.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:28:58 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/17 17:17:23 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_doccer.h" // create_doc, doc_heredoc
#include "parser.h" // t_ast
#include "lexer.h" // TOK_* defines
#include "../minishell.h" // t_status, ERR_* defines
#include <unistd.h> // unlink

t_status	doccer_interpret_unclosed(t_ast *ast)
{
	if (!ast || !ast->token)
		return (ERR_SUCCESS);
	if (doccer_interpret_unclosed(ast->left) != ERR_SUCCESS
		|| doccer_interpret_unclosed(ast->right) != ERR_SUCCESS)
		return (ERR_GENERALERR);
	if (ast->token->desc == TOK_PIPE
		|| ast->token->desc == TOK_AND
		|| ast->token->desc == TOK_OR)
		return (create_doc(ast->right, doc_unclosed));
	return (ERR_SUCCESS);
}

t_status	doccer_delete_heredocs(t_ast *ast)
{
	int		ret_value;

	if (!ast || !ast->token)
		return (ERR_SUCCESS);
	ret_value = doccer_delete_heredocs(ast->left);
	ret_value = doccer_delete_heredocs(ast->right);
	if (ast->token->desc == TOK_REDIR_HEREDOC)
		ret_value = unlink(ast->right->token->word);
	if (ret_value == -1)
		return (ERR_GENERALERR);
	return (ERR_SUCCESS);
}

t_status	doccer_interpret_heredocs(t_ast *ast)
{
	if (!ast || !ast->token)
		return (ERR_SUCCESS);
	if (doccer_interpret_heredocs(ast->left) != ERR_SUCCESS
		|| doccer_interpret_heredocs(ast->right) != ERR_SUCCESS)
		return (ERR_GENERALERR);
	if (ast->token->desc == TOK_REDIR_HEREDOC)
		return (create_doc(ast->right, doc_heredoc));
	return (ERR_SUCCESS);
}
