/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:33:05 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/13 13:42:01 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_PRIVATE_H
# define EXPANDER_PRIVATE_H

// reallocation
char	**realloc_string_array(char **ptr, int size);
char	*ft_realloc(char *ptr, int len);

// expansion
char	*expand_var(char *arg);
char	*get_var(char *arg, int *index);
char	*add_expanded_var(char *result, char *var, int *result_index);

// quotes
char	*handle_quotes(char *result, char *str, int *index, int *result_index);
void	quote_removal(char **argv);
int		find_closing_quote(char *str, int *index, char quote_type);

#endif
