/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_executer.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:14:20 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/23 00:48:25 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_EXECUTER_H
# define PRIVATE_EXECUTER_H

# include "../executer.h" // t_status, t_cmd_table
# include "parser.h" // t_ast
# include <sys/types.h> // pid_t

/* Precedence levels for file descriptor prioritization. */
# define FDLVL_STD 0
# define FDLVL_PIPE 1
# define FDLVL_REDIR 2

// handle funcs
t_cmd_table	*handle_or(t_ast *ast);
t_cmd_table	*handle_and(t_ast *ast);
t_cmd_table	*handle_pipe(t_ast *ast);
t_cmd_table	*handle_redir_heredoc(t_ast *ast);
t_cmd_table	*handle_redir_append(t_ast *ast);
t_cmd_table	*handle_redir_in(t_ast *ast);
t_cmd_table	*handle_redir_out(t_ast *ast);
t_cmd_table	*handle_cmd(t_ast *ast);

// utils
pid_t		exec_cmd(t_cmd_table *cmd_table, int fd_pipe);
void		ms_wait_pid_and_set_exit(pid_t pid);
t_cmd_table	*create_cmd_table(t_ast *ast);

// path
char		*get_cmd_path(char **env, char *cmd);

// error
void		print_error(t_status exit_status, char *error_loc);

static const t_func_handle	g_func_handle_arr[]
	= {
[TOK_WORD] = &handle_cmd,
[TOK_PIPE] = &handle_pipe,
[TOK_REDIR_IN] = &handle_redir_in,
[TOK_REDIR_OUT] = &handle_redir_out,
[TOK_REDIR_HEREDOC] = &handle_redir_heredoc,
[TOK_REDIR_APPEND] = &handle_redir_append,
[TOK_UNCLOSED_SQUOTE] = &handle_cmd,
[TOK_UNCLOSED_DQUOTE] = &handle_cmd,
[TOK_SUBSHELL] = &handle_cmd,
[TOK_AND] = &handle_and,
[TOK_OR] = &handle_or,
[TOK_QUOTED] = &handle_cmd,
};

#endif
