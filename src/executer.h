/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:45:37 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/16 18:43:36 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "parser.h" // t_ast

# define EXEC_SUCCESS 0
# define EXEC_GENERALERR 1 
# define EXEC_SYNTAXERR 2
# define EXEC_CMDNOTFOUND 127
# define EXEC_SIGNAL 128

typedef unsigned char	t_status;

t_status	executer_exec_ast(t_ast *ast, int fd_in, int fd_out);

#endif
