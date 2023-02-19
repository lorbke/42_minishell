/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:28:34 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/19 18:52:56 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOCCER_H
# define DOCCER_H

# include "executer.h" // t_status
# include "parser.h" // t_ast

// unclosed
t_status	doccer_interpret_unclosed_special(t_ast *ast, char **doc_input);
t_status	doccer_interpret_unclosed_quotes(t_ast *ast, char **doc_input);

// heredoc
t_status	doccer_interpret_heredocs(t_ast *ast);
t_status	doccer_delete_heredocs(t_ast *ast);

#endif
