/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:33:05 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/17 09:05:37 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_PRIVATE_H
# define EXPANDER_PRIVATE_H

// @note maybe would make more sense to move this to utils.h
// reallocation
char	**realloc_string_array(char **ptr, int size);
char	*ft_realloc(char *ptr, int len);

// expansion
char	*try_expansion(char *result, char *arg, int *index, int *result_index);
char	*tilde_expansion(char *result, char *arg, int *index, int *result_index);
char	*add_char_to_string(char *result, char c, int *index, int *result_index);

// quotes
char	*handle_quotes(char *result, char *str, int *index, int *result_index);
void	quote_removal(char **argv);
int		find_closing_quote(char *str, int *index, char quote_type);

#endif
