/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:16:25 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 14:28:04 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

// quotes
void	quote_removal(char **argv);
void	remove_quotes_from_string(char *str);

// quotes_utils
char	*handle_quotes(char *result, char *str, int *i, int *result_i);
int		in_closed_quotes(char *result, char *arg, int *i, int *result_i);
int		find_closing_quote(char *str, int *i, char quote_type);
void	skip_quotes_in_quotes(char *str, int *i, int *j);

#endif
