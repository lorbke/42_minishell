/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:45:37 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/26 00:11:23 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "parser.h" // t_ast
# include "minishell.h" // t_status

/* The file descriptor variables are arrays of two, because there has to be a
data structure that is able to not only store the file descriptor, but also 
information about its precedence. E.g. pipe file descriptors must not overwrite
redirection file descriptors. */
typedef struct s_cmd_table
{
	char	**cmd;
	int		fd_in[2];
	int		fd_out[2];
}	t_cmd_table;

typedef t_cmd_table	*(*t_func_handle)(t_ast *);

t_status	executer_exec_ast(t_ast *ast);
void		executer_free_cmd_table(void *cmd_table_void);

#endif
