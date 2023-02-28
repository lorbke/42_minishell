/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_executer.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:14:20 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 16:02:45 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_EXECUTER_H
# define PRIVATE_EXECUTER_H

# include "../executer.h" // t_status, t_cmd_table
# include "parser.h" // t_ast
# include "lexer.h" // TOK_* defines
# include <sys/types.h> // pid_t
# include <stdbool.h> // bool

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
bool		executer_is_quoted(char desc);
bool		executer_is_word(char desc);
t_cmd_table	*redir_get_cmd_table(int redir_fd, t_ast *ast);
t_cmd_table	*create_cmd_table(t_ast *ast);

// exec
pid_t		exec_cmd(t_cmd_table *cmd_table, int fd_pipe);
pid_t		exec_execve(t_cmd_table *cmd_table, int fd_pipe);
pid_t		exec_builtin(t_cmd_table *cmd_table, int fd_pipe, int builtin_id);
pid_t		exec_subshell(t_cmd_table *cmd_table, int fd_pipe);
char		*exec_get_cmd_path(char **env, char *cmd);
void		exec_close_in_out_fds(int fd_in[2], int fd_out[2]);
void		exec_prepare_fds_for_exec(t_cmd_table *cmd_table, int fd_pipe);
pid_t		exec_fork_error(pid_t pid, t_cmd_table *cmd_table);

// handle func array
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
