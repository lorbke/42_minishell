/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_doccer.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:30:19 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 00:45:28 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_DOCCER_H
# define PRIVATE_DOCCER_H

# include "parser.h" // t_ast
# include <stdbool.h> // bool

// utils
int		is_only_whitespace(char *str);
int		is_closed(char *str);

// doc
void	doc_heredoc(char *limiter, int fd_write);
void	doc_completingdoc(char *placeholder, int fd_write);
void	doc_quotedoc(char *quote, int fd_write);
char	*get_doc(void (*doc_func)(char *, int), char *lim);

#endif
