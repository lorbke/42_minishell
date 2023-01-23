/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:45:37 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/23 15:49:14 by lorbke           ###   ########.fr       */
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

t_cmd_table	*create_cmd_table(t_ast *ast);

#endif
