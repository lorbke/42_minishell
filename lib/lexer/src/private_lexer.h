/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_lexer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:15:38 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/26 02:27:30 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_LEXER_H
# define PRIVATE_LEXER_H

# include "lexer.h" // t_token, t_stack

char			*lexer_ft_strsep(
					char **stringp, const char *delim, const char *ignore);
char			*skip_until_after_char(char *str, char c);
unsigned char	desc_word(char *word);
t_token			*create_token(char *word);
t_stack			*create_stack_node(t_token *token);

#endif
