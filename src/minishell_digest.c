/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_digest.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:05:55 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/19 20:25:04 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // macros
#include "mssignal.h" // mssignal_change_mode
#include "lexer.h" // lexer_str_to_tokstack
#include "parser.h" // parser_tokstack_to_ast
#include "doccer.h" // doccer_interpret_heredocs
#include "executer.h" // executer_exec_ast
#include "debugger.h" // debug
#include "libft.h" // ft_strncmp
#include <unistd.h> // file descriptor macros
#include <stdio.h> // printf

#define STR_SYNTAXERR ": syntax error near unexpected token `"

static void	print_syntax_error(int desc, char *error_loc)
{
	if (desc == TOK_SUBSHELL)
		printf("%s%s%s'\n",
			SHELL_NAME, STR_SYNTAXERR, "(");
	else
		printf("%s%s%s'\n",
			SHELL_NAME, STR_SYNTAXERR, error_loc);
}

static t_ast	*input_to_ast(char *input)
{
	t_stack		*tokstack;
	t_ast		*ast;
	t_status	exit_status;

	if (!input)
		return (NULL);
	tokstack = lexer_str_to_tokstack(input, CMD_SEPS, CMD_ESCS);
	debug_lexer(tokstack);
	ast = parser_tokstack_to_ast(&tokstack);
	debug_parser(ast, tokstack);
	if (tokstack)
	{
		print_syntax_error(tokstack->token->desc, tokstack->token->word);
		return (NULL);
	}
	exit_status = doccer_interpret_heredocs(ast);
	if (exit_status != ERR_SUCCESS)
	{
		printf("-----exit status: %d\n", exit_status);
		return (NULL);
	}
	return (ast);
}

static t_ast	*append_right_ast(t_ast *main, t_ast *append)
{
	t_ast	*temp;

	if (!main)
		return (append);
	temp = main;
	while (temp->right && temp->right->right)
		temp = temp->right;
	// free temp->right if exists
	temp->right = append;
	return (main);
}

char	*digest_input(char **input, int fd_in, int fd_out)
{
	t_status	exit_status;
	t_ast		*main_ast;
	t_ast		*closing_ast;
	char		*new_input;

	main_ast = input_to_ast(*input);
	if (!main_ast)
		return (*input);
	new_input = ft_calloc(sizeof(char), ARG_MAX);
	exit_status = doccer_interpret_unclosed_special(main_ast, &new_input);
	if (exit_status != ERR_SUCCESS)
	{
		printf("-----exit status: %d\n", exit_status);
		return (*input);
	}
	if (*new_input)
	{
		closing_ast = input_to_ast(new_input);
		if (!closing_ast)
		{
			printf("-----exit status unexpected end of file: %d\n", 2);
			return (*input);
		}
		append_right_ast(main_ast, closing_ast);
		*input = ft_strjoin(*input, new_input);
		free(new_input);
	}
	new_input = ft_calloc(sizeof(char), ARG_MAX);
	exit_status = doccer_interpret_unclosed_quotes(main_ast, &new_input);
	if (exit_status != ERR_SUCCESS)
	{
		printf("-----exit status unexpected end of file: %d\n", 2);
		return (*input);
	}
	if (*new_input)
	{
		*input = ft_strjoin(*input, new_input);
		free(new_input);
	}
	debug_parser(main_ast, NULL);
	mssignal_change_mode(MSSIG_EXEC);
	exit_status = executer_exec_ast(main_ast, fd_in, fd_out);
	mssignal_change_mode(MSSIG_INTER);
	printf("-----exit status: %d\n", exit_status);
	return (*input);
}
