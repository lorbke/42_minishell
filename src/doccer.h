/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:28:34 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/17 17:05:57 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOCCER_H
# define DOCCER_H

# include "executer.h" // t_status
# include "parser.h" // t_ast


// unclosed
t_status	doccer_interpret_unclosed(t_ast *ast);

// heredoc
t_status	doccer_interpret_heredocs(t_ast *ast);
t_status	doccer_delete_heredocs(t_ast *ast);

#endif
