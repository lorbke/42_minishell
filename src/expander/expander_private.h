/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:33:05 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 20:30:58 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_PRIVATE_H
# define EXPANDER_PRIVATE_H

// expander_try_expansion
char	*try_expansion(char *result, char *arg, int *i, int *result_i);

// expander_utils
char	*tilde_expansion(char *result, char *arg, int *i, int *result_i);
char	*add_expanded_var(char *result, char *var, int *result_i);
char	*get_var(char *arg, int *i);
char	*expand_var(char *arg);

// expander
char	*expander_char_to_str(char *result, char c, int *i, int *result_i);

// quotes
void	quote_removal(char **argv);

// quotes_utils
char	*quotes_handle_quotes(char *result, char *str, int *i, int *result_i);
int		quotes_find_closing_quote(char *str, int *i, char quote_type);
int		quotes_in_closed_quotes(char *arg, int *i);

#endif
