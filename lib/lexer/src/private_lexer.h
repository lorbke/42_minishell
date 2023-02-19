/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_lexer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:15:38 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/19 17:23:09 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_LEXER_H
# define PRIVATE_LEXER_H

# include "lexer.h" // t_token, t_stack

// @todo change overly complicated and ugly handling of parentheses
char			*lexer_ft_strsep(char **stringp, const char *delim, const char *ignore);
int				is_special_char(char *str);
int				is_char_set(char c, char *seps);
unsigned char	desc_word(char *word);
t_token			*create_token(char *word, int len);
t_stack			*create_stack_node(t_token *token);

#endif
