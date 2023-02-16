/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_private.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:15:38 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/12 18:11:48 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PRIVATE_H
# define LEXER_PRIVATE_H

// @todo change overly complicated and ugly handling of parentheses
char	*lexer_ft_strsep(char **stringp, const char *delim, const char *ignore);
char	*insert_sep_around_special(char *src, char *seps);

#endif
