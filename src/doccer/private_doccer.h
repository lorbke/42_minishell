/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_doccer.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:30:19 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/17 17:07:35 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_DOCCER_H
# define PRIVATE_DOCCER_H

# include "../executer.h" // t_status
# include "parser.h" // t_ast

void		doc_heredoc(char *limiter, int fd_write);
void		doc_unclosed(char *line, int fd_write);
t_status	create_doc(t_ast *ast, void (*doc_type)(char *, int));


#endif
