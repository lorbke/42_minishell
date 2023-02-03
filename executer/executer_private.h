/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:14:20 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/24 15:07:54 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_PRIVATE_H
# define EXECUTER_PRIVATE_H

# include "executer.h"
# include "parser.h"

typedef t_cmd_table	*(*t_func_exec)(t_ast *);

t_cmd_table	*exec_pipe(t_ast *ast);
t_cmd_table	*exec_redir_in(t_ast *ast);
t_cmd_table	*exec_redir_out(t_ast *ast);
t_cmd_table	*exec_cmd(t_ast *ast);

#endif
