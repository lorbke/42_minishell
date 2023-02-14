/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:22:03 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/14 19:34:20 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBER_H
# define GLOBBER_H

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

// globbing
char	**globber(char **argv);
char	**add_matching_entry(char **result, char *entry);
char	**create_new_cmd(char **expanded_argv, char **argv);
char	**add_vars(char **expanded_argv, char **result, char **argv);
char	**globbing_outside_cwd(char *path, char *pattern, char **result);
char	**check_for_path(char *pattern, char **result);

// pattern
char	*find_pattern(char *arg, int *index);
char	**pattern_over(char **result, char *entry, char *path);
int		is_match(char *entry, char *pattern);
int		ft_strcmp(const char *s1, const char *s2);

// entries
char	**get_matching_entries(char *path, char *pattern, char **result);

#endif
