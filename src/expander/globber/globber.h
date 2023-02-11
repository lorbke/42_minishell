/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:22:03 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/11 20:33:46 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBER_H
# define GLOBBER_H

#include <dirent.h>

void	globber(char **argv);
char	*concatenate_entries(char **result);
char	*find_pattern(char *arg, int *index);
char	**add_first_entry(char **result, char *entry);
char	**add_matching_entry(char **result, char *entry);
char	**sort_matching_entries(char **result, char *entry);
int		is_match(char *entry, char *pattern);

#endif
