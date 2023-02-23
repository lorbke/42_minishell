/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:33:05 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/23 13:20:15 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_PRIVATE_H
# define EXPANDER_PRIVATE_H

// expansion
char	*try_expansion(char *result, char *arg, int *index, int *result_index);
char	*tilde_expansion(char *result, char *arg, int *index, int *result_index);
char	*add_char_to_str(char *result, char c, int *index, int *result_index);

// quotes
char	*handle_quotes(char *result, char *str, int *index, int *result_index);
void	quote_removal(char **argv);
void	skip_quotes_in_quotes(char *str, int *i, int *j);
int		find_closing_quote(char *str, int *index, char quote_type);
int		in_closed_quotes(char *result, char *arg, int *index, int *result_index);

#endif
