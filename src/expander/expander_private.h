/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:33:05 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/12 16:15:02 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_PRIVATE_H
# define EXPANDER_PRIVATE_H

char	*ft_realloc(char *ptr, int len);
char	**realloc_string_array(char **ptr, int size);
char	*expand_var(char *arg);
char	*get_var(char *arg, int *index);
char	*add_expanded_var(char *result, char *var, int *index);
char	*handle_quotes(char *result, char *str, int *index, int *result_index);
void	quote_removal(char *str);
int		find_closing_quote(char *str, int *index, char quote_type);

#endif
