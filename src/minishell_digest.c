/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_digest.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:05:55 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/27 18:58:24 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // defines
#include "mssignal.h" // mssignal_change_mode
#include "lexer.h" // lexer_str_to_tokstack, lexer_free_tokstack
#include "parser.h" // parser_tokstack_to_ast
#include "doccer.h" // doccer_interpret_heredocs
#include "executer.h" // executer_exec_ast
#include "debugger.h" // debug
#include "libft.h" // ft_strncmp
#include "garbage_collector.h" // gc_add_garbage etc.
#include <unistd.h> // file descriptor macros
#include <stdio.h> // printf
#include <stdbool.h> // bool

static bool	is_input_incomplete_print_error(t_stack *tokstack)
{
	while (tokstack && tokstack->next)
		tokstack = tokstack->next;
	if (tokstack && (tokstack->token->desc == TOK_PIPE
			|| tokstack->token->desc == TOK_AND
			|| tokstack->token->desc == TOK_OR
			|| tokstack->token->word && tokstack->token->word[0] == ')'))
	{
		ms_exit_status_set(ERR_SYNTAX);
		ms_print_syntax_error(0, NULL);
		return (true);
	}
	if ((tokstack && tokstack->token->desc == TOK_UNCLOSED_DQUOTE
			&& ft_is_char_count_uneven(tokstack->token->word, '\"'))
		|| (tokstack->token->desc == TOK_UNCLOSED_SQUOTE
			&& ft_is_char_count_uneven(tokstack->token->word, '\'')))
	{
		ms_exit_status_set(ERR_SYNTAX);
		ms_print_syntax_error(0, NULL);
		return (true);
	}
	return (false);
}

static bool	is_subshell_closed(char *str)
{
	int		depth;

	depth = 0;
	while (*str)
	{
		if (*str == '(')
			depth++;
		else if (*str == ')')
			depth--;
		str++;
	}
	if (!depth)
		return (true);
	return (false);
}

static bool	check_subshell_syntax(t_stack *tokstack)
{
	while (tokstack)
	{
		if (tokstack->token->desc == TOK_SUBSHELL)
		{
			if (tokstack->token->word[0] != '('
				|| tokstack->token->word
				[ft_strlen(tokstack->token->word) - 1] != ')'
				|| ft_strlen(tokstack->token->word) < 3
				|| !is_subshell_closed(tokstack->token->word))
			{
				ms_exit_status_set(ERR_SYNTAX);
				ms_print_syntax_error(TOK_SUBSHELL, tokstack->token->word);
				return (true);
			}
		}
		tokstack = tokstack->next;
	}
	return (false);
}

static t_ast	*digest_parser(t_stack *tokstack)
{
	t_ast	*ast;

	if (check_subshell_syntax(tokstack))
		return (NULL);
	ast = parser_tokstack_to_ast(&tokstack);
	if (ast)
		gc_add_garbage(ast, &parser_free_ast);
	debug_parser(ast);
	if (tokstack)
	{
		ms_exit_status_set(ERR_SYNTAX);
		ms_print_syntax_error(tokstack->token->desc, tokstack->token->word);
		return (NULL);
	}
	return (ast);
}

static char	*digest_docs(t_stack *tokstack, char *input, t_status *exit_status)
{
	input = doccer_interpret_docs(tokstack, input, exit_status);
	debug_lexer(tokstack);
	if (*exit_status != ERR_SUCCESS)
	{
		ms_exit_status_set(*exit_status);
		return (input);
	}
	return (input);
}

char	*ms_digest_input(char *input)
{
	t_stack		*tokstack;
	t_ast		*ast;
	t_status	exit_status;

	tokstack = lexer_str_to_tokstack(input);
	if (!tokstack)
		return (input);
	gc_add_garbage(tokstack, &lexer_free_tokstack);
	debug_lexer(tokstack);
	input = doccer_interpret_docs(tokstack, input, &exit_status);
	debug_lexer(tokstack);
	if (exit_status != ERR_SUCCESS)
	{
		ms_exit_status_set(exit_status);
		return (input);
	}
	if (is_input_incomplete_print_error(tokstack))
		return (input);
	ast = digest_parser(tokstack);
	if (!ast)
		return (input);
	debug_message("\n=========Execution=========\n", 0);
	mssignal_change_mode(MSSIG_EXEC);
	ms_exit_status_set(executer_exec_ast(ast));
	mssignal_change_mode(MSSIG_INTER);
	debug_message("===========================\n", 0);
	return (input);
}
