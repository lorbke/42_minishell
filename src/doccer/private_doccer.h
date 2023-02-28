/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_doccer.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:30:19 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 15:20:32 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_DOCCER_H
# define PRIVATE_DOCCER_H

# include "parser.h" // t_ast
# include <stdbool.h> // bool
# include "../minishell.h" // t_status

// utils
bool	doccer_is_word(char desc);
int		is_incomplete_input(t_stack *tokstack);

// doc
int		doc_heredoc(char *limiter, int fd_write);
int		doc_completingdoc(char *placeholder, int fd_write);
int		doc_quotedoc(char *quote, int fd_write);
char	*get_doc(
			int (*doc_func)(char *, int), char *lim, t_status *exit_status);

#endif
