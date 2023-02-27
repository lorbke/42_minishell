/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:33:05 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/27 16:31:18 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_PRIVATE_H
# define EXPANDER_PRIVATE_H

// expansion
char	*try_expansion(char *result, char *arg, int *i, int *result_i);
char	*tilde_expansion(char *result, char *arg, int *i, int *result_i);
char	*add_char_to_str(char *result, char c, int *i, int *result_i);
char	*expand_var(char *arg);
char	*get_var(char *arg, int *i);
char	*add_expanded_var(char *result, char *var, int *result_i);

// quotes
char	*handle_quotes(char *result, char *str, int *i, int *result_i);
void	quote_removal(char **argv);
void	skip_quotes_in_quotes(char *str, int *i, int *j);
int		find_closing_quote(char *str, int *i, char quote_type);
int		in_closed_quotes(char *result, char *arg, int *i, int *result_i);

#endif
