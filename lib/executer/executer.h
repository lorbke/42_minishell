/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:45:37 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/16 09:41:30 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "parser.h" // t_ast

typedef struct s_cmd_table
{
	char	**cmd;
	int		fd_in;
	int		fd_out;
}	t_cmd_table;

void	executer_exec_ast(t_ast *ast);

#endif
