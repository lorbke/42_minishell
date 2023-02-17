/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:14:20 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/16 09:43:05 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_PRIVATE_H
# define EXECUTER_PRIVATE_H

# include "executer.h"
# include "parser.h"
# include <sys/types.h> // pid_t

typedef t_cmd_table	*(*t_func_handle)(t_ast *);

t_cmd_table	*handle_or(t_ast *ast);
t_cmd_table *handle_and(t_ast *ast);
t_cmd_table	*handle_pipe(t_ast *ast);
t_cmd_table	*handle_redir_heredoc(t_ast *ast);
t_cmd_table	*handle_redir_append(t_ast *ast);
t_cmd_table	*handle_redir_in(t_ast *ast);
t_cmd_table	*handle_redir_out(t_ast *ast);
t_cmd_table	*handle_cmd(t_ast *ast);
pid_t		exec_cmd(t_cmd_table *cmd_table);
t_cmd_table	*create_cmd_table(t_ast *ast);
int			get_heredoc(char *limiter);
char		*get_cmd_path(char **env, char *cmd);

#endif
