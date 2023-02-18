/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:33:05 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/18 13:34:17 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_PRIVATE_H
# define EXPANDER_PRIVATE_H

// expansion
char	*try_expansion(char *result, char *arg, int *index, int *result_index);
char	*tilde_expansion(char *result, char *arg, int *index, int *result_index);
char	*add_char_to_string(char *result, char c, int *index, int *result_index);

// quotes
char	*handle_quotes(char *result, char *str, int *index, int *result_index);
void	quote_removal(char **argv);
int		find_closing_quote(char *str, int *index, char quote_type);

#endif
