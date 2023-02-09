/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:33:19 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/09 15:36:27 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // SHELL_NAME
#include "lexer.h" // TOK_* defines
#include <stdio.h> // printf
#include <string.h> // strerror
#include <sys/errno.h> // errno

void	error_parse_print(int desc, char *error_loc)
{
	// @note ugly edge case, maybe just remove it?
	if (desc == TOK_REDIR_IN
		|| desc == TOK_REDIR_OUT
		|| desc == TOK_REDIR_APPEND
		|| desc == TOK_REDIR_HEREDOC)
		printf("%s: syntax error near unexpected token `%s'\n",
			SHELL_NAME, "newline");
	else
		printf("%s: syntax error near unexpected token `%s'\n",
			SHELL_NAME, error_loc);
}
