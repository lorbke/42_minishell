/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_private.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 10:44:19 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 19:22:00 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBER_PRIVATE_H
# define GLOBBER_PRIVATE_H

# include <dirent.h> // opendir, readdir, closedir
# include <sys/stat.h> // stat

// globber_entry
char	**add_matching_entry(char **result, char *entry);
char	**get_matching_entries(char *path, char *pattern, char **result);

// globber_outside_cwd
char	**globbing_outside_cwd(char *path, char *pattern, char **result);
char	**expand_cwd_dir(char *path, char **result);
char	*create_new_path(char *path, char *entry);

// globber_utils
char	**add_vars(char **exp_argv, char **result, char **argv);
int		is_valid_entry(struct dirent *entry, char *pattern);

// globber_pattern
char	*find_pattern(char *arg, int *i);
char	**pattern_over(char **result, char *entry, char *path);

// globber_pattern_utils
int		is_match(char *entry, char *pattern);

#endif
