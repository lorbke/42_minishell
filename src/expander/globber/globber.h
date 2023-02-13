/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:22:03 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/13 13:45:24 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBER_H
# define GLOBBER_H

#include <dirent.h>

// globbing
char	**globber(char **argv);
char	**add_matching_entry(char **result, char *entry);
char	**create_new_cmd(char **expanded_argv, char **argv);
char	**add_vars(char **expanded_argv, char **result, char **argv);

// pattern
char	*find_pattern(char *arg, int *index);
int		is_match(char *entry, char *pattern);
int		ft_strcmp(const char *s1, const char *s2);

#endif
