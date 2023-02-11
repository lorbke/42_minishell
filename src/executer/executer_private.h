/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:14:20 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/09 15:44:15 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_PRIVATE_H
# define EXECUTER_PRIVATE_H

# include "parser.h" // t_ast
# include <sys/types.h> // pid_t

typedef struct s_cmd_table
{
	char	**cmd;
	int		fd_in;
	int		fd_out;
}	t_cmd_table;

typedef t_cmd_table	*(*t_func_handle)(t_ast *);

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
pid_t		exec_cmd(t_cmd_table *cmd_table);
t_cmd_table	*create_cmd_table(t_ast *ast);

// heredoc
t_cmd_table	*handle_unclosed(t_ast *ast);
int			get_heredoc(void (*heredoc_type)(char *, int), char *limiter);
void		heredoc_big(char *limiter, int fd_write);
void		heredoc_small(char *line, int fd_write);

// path
char		*get_cmd_path(char **env, char *cmd);

// exit_status
char		exit_status_get(void);
void		exit_status_set(char exit_status);
void		print_error(char exit_status, char *error_loc);

static const t_func_handle	g_func_handle_arr[]
	= {
[TOK_WORD] = &handle_cmd,
[TOK_PIPE] = &handle_pipe,
[TOK_REDIR_IN] = &handle_redir_in,
[TOK_REDIR_OUT] = &handle_redir_out,
[TOK_REDIR_HEREDOC] = &handle_redir_heredoc,
[TOK_REDIR_APPEND] = &handle_redir_append,
[TOK_SQUOTE] = &handle_cmd,
[TOK_DQUOTE] = &handle_cmd,
[TOK_SUBSHELL] = &handle_cmd,
[TOK_AND] = &handle_and,
[TOK_OR] = &handle_or,
[TOK_UNCLOSED] = &handle_unclosed,
};

#endif
