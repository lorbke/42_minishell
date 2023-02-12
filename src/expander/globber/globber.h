/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:22:03 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/12 14:01:57 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBER_H
# define GLOBBER_H

#include <dirent.h>

void	globber(char **argv);
char	*concatenate_entries(char **result);
char	*find_pattern(char *arg, int *index);
char	**add_matching_entry(char **result, char *entry);
int		is_match(char *entry, char *pattern);
int		ft_strcmp(const char *s1, const char *s2);

#endif
