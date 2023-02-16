/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_lexer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:15:38 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/16 15:45:37 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_LEXER_H
# define PRIVATE_LEXER_H

// @todo change overly complicated and ugly handling of parentheses
char	*lexer_ft_strsep(char **stringp, const char *delim, const char *ignore);
char	*insert_sep_around_special(char *src, char *seps);

#endif
