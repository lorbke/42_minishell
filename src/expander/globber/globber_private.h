/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_private.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 10:44:19 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/22 22:28:59 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBER_PRIVATE_H
# define GLOBBER_PRIVATE_H

#include <dirent.h> // opendir, readdir, closedir
#include <sys/stat.h> // stat

// globbing
char	*create_new_path(char *path, char *entry);
char	**add_matching_entry(char **result, char *entry);
char	**add_vars(char **expanded_argv, char **result, char **argv);
char	**globbing_outside_cwd(char *path, char *pattern, char **result);
char	**expand_cwd_dir(char *path, char *pattern, char **result);

// pattern
char	*find_pattern(char *arg, int *index);
char	**pattern_over(char **result, char *entry, char *path);
int		is_match(char *entry, char *pattern);
int		ft_strcmp(const char *s1, const char *s2);

// entries
int		is_valid_entry(struct dirent *entry, char *pattern);
char	**get_matching_entries(char *path, char *pattern, char **result);

#endif
