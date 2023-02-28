/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:10:26 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 20:34:50 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../lib/env/env.h" // t_sym_tab

// utils
void	utils_free_split(char **split);
int		utils_ft_strcmp(const char *s1, const char *s2);
int		utils_check_naming_convention(char *var);
int		utils_get_str_array_len(char **array);

// utils_realloc
char	*utils_ft_realloc(char *ptr, int len);
char	**utils_realloc_str_arr(char **ptr, int size);

// utils_error
void	utils_ft_perror(char *cmd, char *str);
void	utils_exit_print_to_stderr(char *str, char *arg);

#endif
